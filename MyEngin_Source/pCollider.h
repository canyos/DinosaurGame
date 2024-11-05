#pragma once
#include "pEntity.h"
#include "pColliderComponent.h"
#include "pEnum.h"
#include "pGameObject.h"

namespace p {
	//using namespace enums;
	class Collider 
	{
	public:
		Collider(eColliderType type);
		~Collider();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		eColliderType GetColliderType() { return mType; }
		Vector2 GetSize() { return mSize; }
		Vector2 GetOffset() { return mOffset; }
		GameObject* GetOwner() { return mOwner; }
		Vector2 GetOriginalSize() { return mOriginalSize; }

		void SetSize(Vector2 size) { mSize = size; }
		void SetOriginalSize(Vector2 size) { mSize = size, mOriginalSize = size; }
		void SetOffset(Vector2 offset) { mOffset = offset; }
		void SetOwner(GameObject* obj) { mOwner = obj; }

	protected:
		Vector2 mOriginalSize;
		Vector2 mSize;
		Vector2 mOffset;
		eColliderType mType;
		GameObject* mOwner;
	};
}


