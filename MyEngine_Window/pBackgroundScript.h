#pragma once
#include "pScript.h"
#include "pTransform.h"
namespace p {
	class BackgroundScript : public Script
	{
	public:
		BackgroundScript();
		~BackgroundScript();

		void Initialize()override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC hdc)override;

		void OnCollisionEnter(Collider* other);
		void OnCollisionStay(Collider* other);
		void OnCollisionExit(Collider* other);
	private:


	private:

	};
}