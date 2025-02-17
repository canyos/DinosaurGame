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
			deltaX = min(200.0f* Time::DeltaTime(), 1.0* max(Time::DeltaTime() * 250.0f, Time::DeltaTime() * 250.0f + activeScene->GetTime()*2.5f));

			for (Collider* collider : GetOwner()->GetComponent<ColliderComponent>()->GetColliders()) {
				Vector2 originalSize = collider->GetOriginalSize(); // Assuming you have a method to get the original size
				collider->SetSize(Vector2(originalSize.x + deltaX, originalSize.y));
			}

			pos.x -= deltaX;
			tr->SetPosition(pos);

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

	void CactusScript::OnCollisionEnter(ColliderComponent* other)
	{
		other->GetOwner()->GetComponent<Animator>()->PlayAnimation(L"die", false);
		SceneManager::GetActiveScene()->stopUpdate();		
	}
	void CactusScript::OnCollisionStay(ColliderComponent * other)
	{
	}
	void CactusScript::OnCollisionExit(ColliderComponent * other)
	{
	}
}

