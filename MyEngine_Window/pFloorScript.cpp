#include "pFloorScript.h"
#include "pRigidBody.h"
#include "pCollider.h"
#include "pGameObject.h"
#include "pAudioSource.h"
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
		Collider* floorCol = this->GetOwner()->GetComponent<Collider>();

		float len = fabs(playerTr->GetPosition().y - floorTr->GetPosition().y);
		float scale = fabs(playerTr->GetPosition().y + playerCol->GetSize().y - floorTr->GetPosition().y);

		//if (len < scale) {
		//	Vector2 playerPos = playerTr->GetPosition();
		//	playerPos.y -= (scale - len) -1.0f;
		//	playerTr->SetPosition(playerPos);
		//}

		Vector2 playerPos = playerTr->GetPosition();
		if (playerPos.y >= 610) {
			playerPos.y = 609;
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

