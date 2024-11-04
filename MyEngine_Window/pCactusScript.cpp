#include "pCactusScript.h"
#include "pInput.h"
#include "pTime.h"
#include "pTransform.h"
#include "pGameObject.h"
#include "pAnimator.h"
#include "pObject.h"
#include "pRigidBody.h"
#include "pCollider.h"
#include "pCollisionManager.h"
#include "pSceneManager.h"

namespace p {
	CactusScript::CactusScript()
		
	{
	}
	CactusScript::~CactusScript()
	{
	}
	void CactusScript::Initialize()
	{

	}
	void CactusScript::Update()
	{
		Scene* activeScene = SceneManager::GetActiveScene();
		if (!activeScene->IsEnd()) {
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			BoxCollider2D* collider = (BoxCollider2D*) ((GetOwner()->GetColliders())[0]);
			Vector2 colSize = collider->GetSize();

			collider->SetSize(Vector2(colSize.x - deltaX / 100.0f, colSize.y)); //원래크기로
			//새로 이동할 거리 계산 후 이동
			deltaX = min(500.0f, 1.0* max(Time::DeltaTime() * 250.0f, Time::DeltaTime() * 250.0f + activeScene->GetTime()*2.5f));
			pos.x -= deltaX;
			tr->SetPosition(pos);

			colSize = collider->GetSize();
			//이동한 경로만큼 collider크기 늘려줌
			collider->SetSize(Vector2(colSize.x + deltaX / 100.0f, colSize.y));

			if (pos.x <= -300.0f) {
				GetOwner()->Death();
			}
		}		
	}
	void CactusScript::LateUpdate()
	{
	}
	void CactusScript::Render(HDC hdc)
	{
	}

	void CactusScript::OnCollisionEnter(Collider* other)
	{
		Collider* cactusCol = this->GetOwner()->GetComponent<Collider>();
		other->GetOwner()->GetComponent<Animator>()->PlayAnimation(L"die", false);
		SceneManager::GetActiveScene()->stopUpdate();
		
		
	}
	void CactusScript::OnCollisionStay(Collider * other)
	{
	}
	void CactusScript::OnCollisionExit(Collider * other)
	{
	}
}

