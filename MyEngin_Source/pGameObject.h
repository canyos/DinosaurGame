#pragma once
#include "CommonInclude.h"
#include "pComponent.h"
#include "pEntity.h"
namespace p {
	//actor
	class GameObject : public Entity
	{
	public:
		
		enum class eState {
			Active,
			Paused,
			Dead,
			End,
		};
		GameObject();
		~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			comp->Initialize();
			comp->SetOwner(this);
			
			mComponents[(UINT)comp->GetType()] = comp;

			return comp;
		}

		template <typename T>
		T* GetComponent()
		{
			T* component = nullptr;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component)
					break;
			}

			return component;
		}

		eState GetState() { return mState; }
		void SetActive(bool power) {
			if (power) {
				mState = eState::Active;
			}
			else {
				mState = eState::Paused;
			}
		}
		bool IsActive() { return mState == eState::Active; }
		void Death() { mState = eState::Dead; }
		void SetLayerType(eLayerType layerType) { mLayerType = layerType; }
		eLayerType GetLayerType() { return mLayerType; }
	private:
		void InitializeTransform();
		
	private:
		eState mState;
		std::vector<Component*> mComponents;
		eLayerType mLayerType;
	};
	typedef std::vector<GameObject*>::iterator GameObjectIter;
}


