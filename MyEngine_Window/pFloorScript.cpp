#include "pFloorScript.h"
#include "pRigidBody.h"
#include "pCollider.h"
#include "pGameObject.h"
#include "pAudioSource.h"
#include "pBoxCollider2D.h"
#include <typeinfo>
#include "pCircleCollider2D.h"
namespace p {
	FloorScript::FloorScript()
	{
	}
	FloorScript::~FloorScript()
	{
	}
	void FloorScript::Initialize()
	{
	}
	void FloorScript::Update()
	{
	}
	void FloorScript::LateUpdate()
	{
	}
	void FloorScript::Render(HDC hdc)
	{
	}
	void FloorScript::OnCollisionEnter(ColliderComponent * other)
	{
		RigidBody* rb = other->GetOwner()->GetComponent<RigidBody>();
		Transform* playerTr = other->GetOwner()->GetComponent<Transform>();
		Vector2 playerPos = playerTr->GetPosition();
	

		Transform* floorTr = this->GetOwner()->GetComponent<Transform>();
		//BoxCollider2D* floorCol = (BoxCollider2D*)(this->GetOwner()->GetColliders())[0];

		float playerBottomY=0;
		const std::vector<Collider*>& colliders = other->GetColliders();
		for (Collider* col : colliders) {
			playerBottomY = max(playerBottomY, playerPos.y + col->GetSize().y);
		}

		float floorTopY = floorTr->GetPosition().y;
		float distance = playerBottomY - floorTopY;

		if (distance > 0) {
			// �÷��̾ �ٴ� ���� ���� (1.0f�� �߰� ������)
			playerPos.y -= distance + 1.0f; // 1.0f�� �÷��̾ �ٴ� ���� �о�� ������
			playerTr->SetPosition(playerPos);
		}


		//GetOwner()->GetComponent<AudioSource>()->Play();
		rb->SetGround(true);
	}
	void FloorScript::OnCollisionStay(ColliderComponent * other)
	{
		/*Transform* playerTr = other->GetOwner()->GetComponent<Transform>();
		Vector2 playerPos = playerTr->GetPosition();
		if (playerPos.y >= 610) {
			playerPos.y = 609;
			playerTr->SetPosition(playerPos);
		}*/
	}
	void FloorScript::OnCollisionExit(ColliderComponent * other)
	{
	}
}

