#include "pCollider.h"

namespace p {
	Collider::Collider(eColliderType type) {
		mType = type;
		mSize = Vector2::Zero;
		mOffset = Vector2::Zero;
		mOwner = nullptr;
	}
	Collider::~Collider() {

	}
	void Collider::Initialize()
	{
	}
	void Collider::Update()
	{
	}
	void Collider::LateUpdate()
	{
	}
	void Collider::Render(HDC hdc)
	{
	}
}