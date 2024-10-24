#pragma once
#include "pEntity.h"
#include "CommonInclude.h"
#include "pGameObject.h"

namespace p {
	class Layer : public Entity
	{
	public:
		Layer();
		~Layer();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);
		virtual void Destroy();
		void AddGameObject(GameObject* gameObject);
		const std::vector<GameObject*> GetGameObjects() { return mGameObjects; }
		void EraseGameObjects(GameObject* eraseGameObj);
	private:
		enums::eLayerType mType;
		std::vector<GameObject*> mGameObjects;
	};

}

