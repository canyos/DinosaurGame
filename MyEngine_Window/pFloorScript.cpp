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
	void FloorScript::OnCollisionEnter(Collider * other)
	{
		RigidBody* rb = other->GetOwner()->GetComponent<RigidBody>();
		Transform* playerTr = other->GetOwner()->GetComponent<Transform>();
		Collider* playerCol = other;

		Transform* floorTr = this->GetOwner()->GetComponent<Transform>();
		BoxCollider2D* floorCol = (BoxCollider2D*)(this->GetOwner()->GetColliders())[0];

		float playerBottomY;
		if (typeid(*playerCol) == typeid(BoxCollider2D)) {
			playerBottomY = playerTr->GetPosition().y + ((BoxCollider2D*)playerCol)->GetSize().y*100;
		}
		if (typeid(*playerCol) == typeid(CircleCollider2D)) {
			playerBottomY = playerTr->GetPosition().y + ((CircleCollider2D*)playerCol)->GetRadius();
		}

		float floorTopY = floorTr->GetPosition().y;
		float distance = playerBottomY - floorTopY;

		if (distance > 0) {
			// 플레이어를 바닥 위로 조정 (1.0f는 추가 오프셋)
			Vector2 playerPos = playerTr->GetPosition();
			playerPos.y -= distance + 1.0f; // 1.0f는 플레이어를 바닥 위로 밀어내는 오프셋
			playerTr->SetPosition(playerPos);
		}


		//GetOwner()->GetComponent<AudioSource>()->Play();
		rb->SetGround(true);
	}
	void FloorScript::OnCollisionStay(Collider * other)
	{
		/*Transform* playerTr = other->GetOwner()->GetComponent<Transform>();
		Vector2 playerPos = playerTr->GetPosition();
		if (playerPos.y >= 610) {
			playerPos.y = 609;
			playerTr->SetPosition(playerPos);
		}*/
	}
	void FloorScript::OnCollisionExit(Collider * other)
	{
	}
}

