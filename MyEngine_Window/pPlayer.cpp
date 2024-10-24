#include "pPlayer.h"
#include "pInput.h"
#include "pTransform.h"
#include "pTime.h"

namespace p
{
	void Player::Initialize()
	{
		GameObject::Initialize();
	}

	void Player::Update()
	{
		GameObject::Update();
	}

	void Player::LateUpdate()
	{
		GameObject::LateUpdate();
		
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}