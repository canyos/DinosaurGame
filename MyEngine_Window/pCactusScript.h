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

		void OnCollisionEnter(Collider* other);
		void OnCollisionStay(Collider* other);
		void OnCollisionExit(Collider* other);
	private:
		float deltaX = 0;
		int x = 0;
	private:

	};
}

