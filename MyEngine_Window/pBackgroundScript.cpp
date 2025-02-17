#include "pBackgroundScript.h"
#include "pInput.h"
#include "pTime.h"
#include "pTransform.h"
#include "pGameObject.h"
#include "pAnimator.h"
#include "pObject.h"
#include "pRigidBody.h"
#include "pCollider.h"
#include "pCollisionManager.h"
namespace p {
	BackgroundScript::BackgroundScript()

	{
	}
	BackgroundScript::~BackgroundScript()
	{
	}
	void BackgroundScript::Initialize()
	{

	}
	void BackgroundScript::Update()
	{
		Scene* activeScene = SceneManager::GetActiveScene();
		if (!activeScene->IsEnd()) {
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos.x -= min(300.0f * Time::DeltaTime(),max(Time::DeltaTime() * 300.0f,Time::DeltaTime() * 300.0f + activeScene->GetTime()*3.0f));

			if (pos.x <= -800.0f) {
				pos.x += 2400.0f;
			}
			tr->SetPosition(pos);
		}
	}
	void BackgroundScript::LateUpdate()
	{
	}
	void BackgroundScript::Render(HDC hdc)
	{
	}

	void BackgroundScript::OnCollisionEnter(ColliderComponent* other)
	{
	}
	void BackgroundScript::OnCollisionStay(ColliderComponent * other)
	{
	}
	void BackgroundScript::OnCollisionExit(ColliderComponent * other)
	{
	}
}
