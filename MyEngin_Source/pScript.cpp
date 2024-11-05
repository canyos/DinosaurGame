#include "pScript.h"
#include "pCollider.h"
namespace p {
	Script::Script():Component(enums::eComponentType::Script)
	{
	}
	Script::~Script()
	{
	}
	void Script::Initialize()
	{
	}
	void Script::Update()
	{
	}
	void Script::LateUpdate()
	{
	}
	void Script::Render(HDC hdc)
	{
	}
	void Script::OnCollisionEnter(ColliderComponent* other)
	{
	}
	void Script::OnCollisionStay(ColliderComponent* other)
	{
	}
	void Script::OnCollisionExit(ColliderComponent* other)
	{
	}
}