#pragma once
#include "pScript.h"
#include "pTransform.h"
namespace p {
	class CactusScript : public Script
	{
	public:
		CactusScript();
		~CactusScript();

		void Initialize()override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC hdc)override;

		void OnCollisionEnter(ColliderComponent* other);
		void OnCollisionStay(ColliderComponent* other);
		void OnCollisionExit(ColliderComponent* other);
	private:
		float deltaX = 0;
		int x = 0;
	private:

	};
}

