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
		
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos.x -= Time::DeltaTime() * 250.0f;
		tr->SetPosition(pos);
		
		
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
		SceneManager::GetActiveScene()->stopUpdate();
		
		other->GetOwner()->GetComponent<Animator>()->PlayAnimation(L"die", false);
	}
	void CactusScript::OnCollisionStay(Collider * other)
	{
	}
	void CactusScript::OnCollisionExit(Collider * other)
	{
	}
}

