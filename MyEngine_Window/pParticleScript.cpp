#include "pParticleScript.h"
#include "pGameObject.h"
#include "pTransform.h"
#include "pTime.h"
#include "pParticle.h"
#include "pSceneManager.h"
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
		Scene* activeScene = SceneManager::GetActiveScene();
		if (!activeScene->IsEnd()) {
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			GameObject* gameObj = GetOwner();
			Particle* particle = (Particle*)gameObj;
			float speed = particle->GetSpeed();

			pos.x -= min(speed*1.5, (speed + activeScene->GetTime()*3.0f)) * Time::DeltaTime();
			tr->SetPosition(pos);

			if (pos.x <= -100.0f) {
				GetOwner()->Death();
			}
		}
	}
	void ParticleScript::LateUpdate()
	{
	}
	void ParticleScript::Render(HDC hdc)
	{
	}
}

