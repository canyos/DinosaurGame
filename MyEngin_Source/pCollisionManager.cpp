#include "pCollisionManager.h"
#include "pScene.h"
#include "pSceneManager.h"
#include "pGameObject.h"
#include "pCollider.h"
#include "pTransform.h"
#include "pGameObject.h"
#include <map>

namespace p {
	std::bitset<(UINT)eLayerType::Max> CollisionManager::mCollisionLayerMatrix[(UINT)eLayerType::Max] = {};
	std::unordered_map<UINT64, bool> CollisionManager::mCollisionMap = {};
	
	void CollisionManager::Initialize()
	{
	}
	void CollisionManager::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();
		for (UINT row = 0; row < (UINT)eLayerType::Max; row++) {
			for (UINT col = 0; col < (UINT)eLayerType::Max; col++) {
				if (mCollisionLayerMatrix[row][col]) {
					LayerCollision(scene, (eLayerType)row, (eLayerType)col);
				}
			}
		}
	}
	void CollisionManager::LateUpdate()
	{
	}
	void CollisionManager::Render(HDC hdc)
	{
	}
	void CollisionManager::Clear()
	{
		mCollisionMap.clear();
		mCollisionLayerMatrix->reset();
	}
	void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
		int row=0, col=0;
		if (left <= right) {
			row = (UINT)left;
			col = (UINT)right;
		}
		else {
			row = (UINT)right;
			col = (UINT)left;
		}
		mCollisionLayerMatrix[row][col] = enable;
	}

	void CollisionManager::LayerCollision(Scene * scene, eLayerType left, eLayerType right)
	{
		const std::vector<GameObject*>& lefts = SceneManager::GetGameObjects(left);
		const std::vector<GameObject*>& rights = SceneManager::GetGameObjects(right);

		for (GameObject* left : lefts) {
			if (left->IsActive() == false) 
				continue;

			std::vector<Collider*> leftCols = left->GetColliders();
			if (leftCols.empty()) {
				continue;
			}

			for (GameObject* right : rights) {
				if (right->IsActive() == false) 
					continue;
				
				std::vector<Collider*> rightCols = right->GetColliders();
				if (rightCols.empty()) {
					continue;
				}

				if (left == right)
					continue;

				for (auto leftCol : leftCols) {
					for (auto rightCol : rightCols) {
						ColliderCollision(leftCol, rightCol);
					}
				}
				
			}
		}
	}
	void CollisionManager::ColliderCollision(Collider * left, Collider * right)
	{
		//�浹üũ ���� 
		//�� �浹ü ��ȣ�� ������ ID�� Ȯ���� CollisionId���� ����
		CollisionID id = {};
		id.left = left->GetID();
		id.right = right->GetID();

		auto iter = mCollisionMap.find(id.id);
		if (iter == mCollisionMap.end()) {
			mCollisionMap.insert({ id.id,false });
			iter = mCollisionMap.find(id.id);
		}
		//�浹 üũ
		if(Intersect(left, right)) {
			if (iter->second == false) {
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				iter->second = true;
			}
			else {
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else {
			if (iter->second == true) {
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
				iter->second = false;
			}
		}

	}
	bool CollisionManager::Intersect(Collider * left, Collider * right)
	{
		Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

		Vector2 leftPos = leftTr->GetPosition() + left->GetOffset();
		Vector2 rightPos = rightTr->GetPosition() + right->GetOffset();

		

		enums::eColliderType leftType = left->GetColliderType();
		enums::eColliderType rightType = right->GetColliderType();

		if (leftType == enums::eColliderType::Rect2D &&
			rightType == enums::eColliderType::Rect2D) {
			//rect-rect
			Vector2 leftSize = ((BoxCollider2D*) left)->GetSize() *100.0f;
			Vector2 rightSize = ((BoxCollider2D*) right)->GetSize() *100.0f;

			if (fabs(leftPos.x + leftSize.x/2.0f - (rightPos.x + rightSize.x/2.0f)) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f) &&
				fabs(leftPos.y  + leftSize.y / 2.0f - (rightPos.y + rightSize.y / 2.0f)) < fabs(leftSize.y / 2.0f + rightSize.y / 2.0f)) {
				return true;
			}
		}
		
		if (leftType == enums::eColliderType::Circle2D &&
			rightType == enums::eColliderType::Circle2D) {
			//circle-circle
			float leftRadius = ((CircleCollider2D*)left)->GetRadius() * 100.0f;
			float rightRadius = ((CircleCollider2D*)right)->GetRadius() * 100.0f;

			Vector2 leftCirclePos = Vector2(leftPos.x + leftRadius, leftPos.y + leftRadius); ;
			Vector2 rightCirclePos = Vector2(rightPos.x + rightRadius, rightPos.y + rightRadius);

			float distance = (leftCirclePos - rightCirclePos).length();
			if (distance <= (leftRadius) + (rightRadius)) {
				return true;
			}
		}
		
		if (leftType == enums::eColliderType::Rect2D &&
			rightType == enums::eColliderType::Circle2D) {
			//rect-circle
			//�� ������ ��ŭ �簢�� �����ڸ� Ȯ���� 
			//�� ������ �������� �Ÿ��� r���� ������
			return checkCollideCircleRect(right, left);
			
		}
		if (leftType == enums::eColliderType::Circle2D &&
			rightType == enums::eColliderType::Rect2D) {
			//circle-rect
			return checkCollideCircleRect(left, right);
		}
		return false;
	}
	bool CollisionManager::checkCollideCircleRect(Collider * circleCol, Collider * rectCol)
	{
		CircleCollider2D* circle = (CircleCollider2D*)circleCol;
		BoxCollider2D* rect = (BoxCollider2D*)rectCol;

		Transform* circleTr = circle->GetOwner()->GetComponent<Transform>();
		Transform* rectTr = rect->GetOwner()->GetComponent<Transform>();

		float radius = circle->GetRadius(); //������
		Vector2 rectSize = rect->GetSize() *100.0f; //�簢�� ���μ���

		Vector2 circlePos = Vector2(circleTr->GetPosition().x + circle->GetOffset().x + radius,
			circleTr->GetPosition().y + circle->GetOffset().y + radius);//���� �߽�
		Vector2 rectPos = rectTr->GetPosition() + rect->GetOffset();//�簢�� ������

		 // �簢���� ���� ����� ���� ã��
		float closestX = (circlePos.x < rectPos.x) ? rectPos.x :
			(circlePos.x > rectPos.x + rectSize.x) ? rectPos.x + rectSize.x :
			circlePos.x;

		float closestY = (circlePos.y < rectPos.y) ? rectPos.y :
			(circlePos.y > rectPos.y + rectSize.y) ? rectPos.y + rectSize.y :
			circlePos.y;

		// ���� �߽ɰ� ���� ����� �� ���� �Ÿ� ���
		float distanceX = circlePos.x - closestX;
		float distanceY = circlePos.y - closestY;

		return (distanceX * distanceX + distanceY * distanceY) <= (radius * radius);
	}
}