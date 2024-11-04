#pragma once
#include "pCollider.h"

namespace p{
	class CircleCollider2D : public Collider
	{
	public:
		CircleCollider2D();
		~CircleCollider2D();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		float GetRadius() { return mRadius; }
		void SetRadius(float r) { mRadius = r; }
	private:
		float mRadius;
	};
}


