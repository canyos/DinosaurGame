#include "pCollisionManager.h"
#include "pScene.h"
#include "pSceneManager.h"
#include "pGameObject.h"
#include "pCollider.h"
#include "pTransform.h"
#include "pGameObject.h"
#include <map>
#include "pColliderComponent.h"

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

	void CollisionManager::LayerCollision(Scene * scene, eLayerType leftLayer, eLayerType rightLayer)
	{
		const std::vector<GameObject*>& lefts = SceneManager::GetGameObjects(leftLayer);
		const std::vector<GameObject*>& rights = SceneManager::GetGameObjects(rightLayer);

		for (GameObject* left : lefts) {
			if (left->IsActive() == false) 
				continue;

			const std::vector<Collider*>& leftCols = left->GetComponent<ColliderComponent>()->GetColliders();
			if (leftCols.empty()) {
				continue;
			}

			for (GameObject* right : rights) {
				if (right->IsActive() == false) 
					continue;
				
				const std::vector<Collider*>& rightCols = right->GetComponent<ColliderComponent>()->GetColliders();
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
		//충돌체크 로직 
		//두 충돌체 번호를 가져온 ID를 확인해 CollisionId값을 세팅
		CollisionID id = {};
		ColliderComponent* leftComp = left->GetOwner()->GetComponent<ColliderComponent>();
		id.left = leftComp->GetID();
		ColliderComponent* rightComp = right->GetOwner()->GetComponent<ColliderComponent>();
		id.right = rightComp->GetID();

		auto iter = mCollisionMap.find(id.id);
		if (iter == mCollisionMap.end()) {
			mCollisionMap.insert({ id.id,false });
			iter = mCollisionMap.find(id.id);
		}

		//충돌 체크
		if(Intersect(left, right)) {
			if (iter->second == false) {
				leftComp->OnCollisionEnter(rightComp);
				rightComp->OnCollisionEnter(leftComp);
				iter->second = true;
			}
			else {
				leftComp->OnCollisionStay(rightComp);
				rightComp->OnCollisionStay(leftComp);
			}
		}
		else {
			if (iter->second == true) {
				leftComp->OnCollisionExit(rightComp);
				rightComp->OnCollisionExit(leftComp);
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

		Vector2 leftSize = left->GetSize();
		Vector2 rightSize = right->GetSize();

		if (leftType == enums::eColliderType::Rect2D &&
			rightType == enums::eColliderType::Rect2D) {
			//rect-rect
			if (fabs(leftPos.x + leftSize.x/2.0f - (rightPos.x + rightSize.x/2.0f)) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f) &&
				fabs(leftPos.y  + leftSize.y / 2.0f - (rightPos.y + rightSize.y / 2.0f)) < fabs(leftSize.y / 2.0f + rightSize.y / 2.0f)) {
				return true;
			}
		}
		
		if (leftType == enums::eColliderType::Circle2D &&
			rightType == enums::eColliderType::Circle2D) {
			//circle-circle
			Vector2 leftCenterPos = Vector2(leftPos.x + leftSize.x/2.0f, leftPos.y + leftSize.y / 2.0f); 
			Vector2 rightCenterPos = Vector2(rightPos.x + rightSize.x / 2.0f, rightPos.y + rightSize.y / 2.0f);

			float distance = (leftCenterPos - rightCenterPos).length();
			if (distance <= (leftSize.x/2.0f) + (rightSize.x/2.0f)) {
				return true;
			}
		}
		
		if (leftType == enums::eColliderType::Rect2D &&
			rightType == enums::eColliderType::Circle2D) {
			//rect-circle
			//원 반지름 만큼 사각형 가장자리 확장해 
			//원 중점과 꼭짓점의 거리가 r보다 작은지
			return checkCollideCircleRect(right, left);
			
		}
		if (leftType == enums::eColliderType::Circle2D &&
			rightType == enums::eColliderType::Rect2D) {
			//circle-rect
			return checkCollideCircleRect(left, right);
		}
		return false;
	}
	bool CollisionManager::checkCollideCircleRect(Collider * circle, Collider * rect)
	{
		Transform* circleTr = circle->GetOwner()->GetComponent<Transform>();
		Transform* rectTr = rect->GetOwner()->GetComponent<Transform>();

		float radius = circle->GetSize().x/2.0f; //반지름
		Vector2 rectSize = rect->GetSize(); //사각형 가로세로

		Vector2 circleCenterPos = Vector2(circleTr->GetPosition().x + circle->GetOffset().x + radius,
			circleTr->GetPosition().y + circle->GetOffset().y + radius);//원의 중심
		Vector2 rectPos = rectTr->GetPosition() + rect->GetOffset();//사각형 왼쪽위

		 // 사각형의 가장 가까운 점을 찾기
		float closestX = (circleCenterPos.x < rectPos.x) ? rectPos.x :
			(circleCenterPos.x > rectPos.x + rectSize.x) ? rectPos.x + rectSize.x :
			circleCenterPos.x;

		float closestY = (circleCenterPos.y < rectPos.y) ? rectPos.y :
			(circleCenterPos.y > rectPos.y + rectSize.y) ? rectPos.y + rectSize.y :
			circleCenterPos.y;

		// 원의 중심과 가장 가까운 점 간의 거리 계산
		float distanceX = circleCenterPos.x - closestX;
		float distanceY = circleCenterPos.y - closestY;

		return (distanceX * distanceX + distanceY * distanceY) <= (radius * radius);
	}
}