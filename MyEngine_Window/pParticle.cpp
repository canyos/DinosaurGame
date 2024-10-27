#include "pParticle.h"

namespace p {
	void Particle::Initialize()
	{
		GameObject::Initialize();
	}
	void Particle::Update()
	{
		GameObject::Update();
	}
	void Particle::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Particle::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}