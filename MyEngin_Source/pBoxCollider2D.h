#pragma once
#include "pCollider.h"

namespace p {
	class BoxCollider2D : public Collider
	{
	public:
		BoxCollider2D();
		~BoxCollider2D();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		Vector2 GetSize() { return mSize; }
		void SetSize(Vector2 size) { mSize = size; }
	private:
		Vector2 mSize;

	};
}

