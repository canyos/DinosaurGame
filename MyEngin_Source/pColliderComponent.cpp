#include "pColliderComponent.h"
#include "pScript.h"
#include "pGameObject.h"
namespace p {
	UINT32 ColliderComponent::mCollisionID = 1;
	ColliderComponent::ColliderComponent() :
		Component(eComponentType::ColliderComponent),
		mID(mCollisionID++)
	{
		mColliders = {};
	}

	ColliderComponent::~ColliderComponent()
	{

	}

	void ColliderComponent::Initialize()
	{
		for (auto col : mColliders) {
			col->Initialize();
		}
	}

	void ColliderComponent::Update()
	{
		for (auto col : mColliders) {
			col->Update();
		}
	}

	void ColliderComponent::LateUpdate()
	{
		for (auto col : mColliders) {
			col->LateUpdate();
		}
	}

	void ColliderComponent::Render(HDC hdc)
	{
		for (auto col : mColliders) {
			col->Render(hdc);
		}
	}

	void ColliderComponent::OnCollisionEnter(ColliderComponent * other)
	{
		Script* script = GetOwner()->GetComponent<Script>();
		script->OnCollisionEnter(other);
	}

	void ColliderComponent::OnCollisionStay(ColliderComponent * other)
	{
		Script* script = GetOwner()->GetComponent<Script>();
		script->OnCollisionStay(other);
	}

	void ColliderComponent::OnCollisionExit(ColliderComponent * other)
	{
		Script* script = GetOwner()->GetComponent<Script>();
		script->OnCollisionStay(other);
	}
}

