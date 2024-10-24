#include "pLayer.h"
namespace p {
	Layer::Layer() : mGameObjects {}
	{
	}
	Layer::~Layer()
	{
		for (GameObject* gameobj : mGameObjects) {
			if (gameobj == nullptr)
				continue;

			delete gameobj;
			gameobj = nullptr;
		}
	}
	void Layer::Initialize()
	{
		for (GameObject* gameObj : mGameObjects) {
			if (gameObj == nullptr)
				continue;

			gameObj->Update();
		}
	}
	void Layer::Update()
	{
		for (GameObject* gameObj : mGameObjects) {
			if (gameObj == nullptr)
				continue;
			if (gameObj->IsActive() == false)
				continue;
			gameObj->Update();
		}
	}
	void Layer::LateUpdate()
	{
		for (GameObject* gameObj : mGameObjects) {
			if (gameObj == nullptr)
				continue;
			if (gameObj->IsActive() == false)
				continue;
			gameObj->LateUpdate();
		}
	}

	void Layer::Render(HDC hdc)
	{
		for (GameObject* gameObj : mGameObjects) {
			if (gameObj == nullptr)
				continue;
			if (gameObj->IsActive() == false)
				continue;
			gameObj->Render(hdc);
		}
			
	}

	void Layer::Destroy()
	{
		for (GameObjectIter iter = mGameObjects.begin()
			; iter != mGameObjects.end()
			; )
		{
			GameObject::eState active = (*iter)->GetState();
			if (active == GameObject::eState::Dead)
			{
				GameObject* deathObj = (*iter);
				iter = mGameObjects.erase(iter);

				delete deathObj;
				deathObj = nullptr;

				continue;
			}

			iter++;
		}
	}
	
	void Layer::AddGameObject(GameObject * gameObject)
	{
		if (gameObject == nullptr)
			return;
		mGameObjects.push_back(gameObject);
	}
	void Layer::EraseGameObjects(GameObject * eraseGameObj)
	{
		mGameObjects.erase(
			std::remove_if(mGameObjects.begin(), mGameObjects.end(),
				[=](GameObject* gameObj)
				{
					return (gameObj == eraseGameObj);
				}),
			mGameObjects.end());
	}
}