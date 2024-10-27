#include "pParticleScript.h"
#include "pGameObject.h"
#include "pTransform.h"
#include "pTime.h"
#include "pParticle.h"
namespace p {
	ParticleScript::ParticleScript()
	{
	}
	ParticleScript::~ParticleScript()
	{
	}
	void ParticleScript::Initialize()
	{
	}
	void ParticleScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		GameObject* gameObj = GetOwner();
		Particle* particle = (Particle*)gameObj;
		float speed = particle->GetSpeed();
		
		pos.x -= Time::DeltaTime() * speed;
		tr->SetPosition(pos);

		if (pos.x <= -100.0f) {
			GetOwner()->Death();
		}
	}
	void ParticleScript::LateUpdate()
	{
	}
	void ParticleScript::Render(HDC hdc)
	{
	}
}

