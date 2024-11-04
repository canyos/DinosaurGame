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
		mColliders = {};
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
		for (Collider* col : mColliders)
		{
			if (col == nullptr)
				continue;
			delete col;
			col = nullptr;
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
		for (Collider* col : mColliders)
		{
			if (col == nullptr)
				continue;

			col->Initialize();
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
		for (Collider* col : mColliders)
		{
			if (col == nullptr)
				continue;
			col->Update();
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
		for (Collider* col : mColliders)
		{
			if (col == nullptr)
				continue;
			col->LateUpdate();
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
		for (Collider* col : mColliders)
		{
			if (col == nullptr)
				continue;
			col->Render(hdc);
		}
	}
	void GameObject::InitializeTransform() {
		AddComponent<Transform>();
	}

}