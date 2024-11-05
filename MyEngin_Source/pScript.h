#pragma once
#include "pComponent.h"

namespace p {
	class Script:public Component
	{
	public:
		Script();
		~Script();
		void Initialize()override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC hdc)override;

		virtual void OnCollisionEnter(class ColliderComponent* other);
		virtual void OnCollisionStay(class ColliderComponent* other);
		virtual void OnCollisionExit(class ColliderComponent* other);
	private:

	};
}


