#pragma once
#include "pEntity.h"
#include "pGameObject.h"
#include "pLayer.h"
namespace p {
	class Scene : public Entity {
	public:
		Scene();
		~Scene();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);
		virtual void Destroy();

		virtual void OnEnter();//Scene에 들어가거나 
		virtual void OnExit();//나갈때 필요없는거 처리
		
		void AddGameObject(GameObject* gameObject, enums::eLayerType type);
		void EraseGameObject(GameObject* gameObj);
		Layer* GetLayer(const enums::eLayerType type) { return mLayers[(UINT)type]; }

	private:
		std::vector<Layer*> mLayers;
	};
}


