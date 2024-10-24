#include "pAudioListener.h"
#include "pTransform.h"
#include "pGameObject.h"
#include "pFmod.h"
namespace p {
	AudioListener::AudioListener()
		: Component(eComponentType::AudioListener)
	{
	}
	AudioListener::~AudioListener()
	{
	}
	void AudioListener::Initialize()
	{
	}
	void AudioListener::Update()
	{
	}
	void AudioListener::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Fmod::Set3DListenerAttributes(&pos);
	}
	void AudioListener::Render(HDC hdc)
	{
	}
}
