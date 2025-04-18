#include "pFloor.h"
#include "pInput.h"
#include "pTransform.h"
#include "pTime.h"

namespace p
{
	Floor::Floor()
	{
	}
	Floor::~Floor()
	{
	}
	void Floor::Initialize()
	{
		GameObject::Initialize();
	}

	void Floor::Update()
	{
		GameObject::Update();
	}

	void Floor::LateUpdate()
	{
		GameObject::LateUpdate();

	}

	void Floor::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}