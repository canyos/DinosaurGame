#include "pGameObject.h"
#include "pInput.h"
#include "pTime.h"
#include "pTransform.h"
namespace p {
	GameObject::GameObject()
		:mState(eState::Active), 
		 mLayerType(eLayerType::None)
	{
		mComponents.resize((UINT)enums::eComponentType::End);
		InitializeTransform();
	}

	GameObject::~GameObject()
	{
		
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			delete comp;
			comp = nullptr;
		}
	}

	void GameObject::Initialize()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			comp->Initialize();
		}
	}


	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			comp->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			comp->LateUpdate();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			comp->Render(hdc);
		}
	}
	void GameObject::InitializeTransform() {
		AddComponent<Transform>();
	}

}