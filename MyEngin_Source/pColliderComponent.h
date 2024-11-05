#pragma once
#include <vector>
#include "pComponent.h"
#include "pCollider.h"

namespace p {
	class Collider;

	class ColliderComponent : public Component
	{
	public:
		ColliderComponent();
		~ColliderComponent();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(ColliderComponent* other);
		virtual void OnCollisionStay(ColliderComponent* other);
		virtual void OnCollisionExit(ColliderComponent* other);

		UINT32 GetID() { return mID; }

		void AddCollider(Collider* col) { 
			mColliders.push_back(col); 
		}

		std::vector<Collider*> GetColliders() { return mColliders; }

	private:
		std::vector<Collider*> mColliders;

		static UINT32 mCollisionID;
		UINT32 mID;
	};
}

