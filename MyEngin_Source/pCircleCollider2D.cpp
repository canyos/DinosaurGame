#include "pCircleCollider2D.h"
#include "pTransform.h"
#include "pGameObject.h"
#include "pRenderer.h"
#include "pCamera.h"

namespace p {
	CircleCollider2D::CircleCollider2D()
		: Collider(enums::eColliderType::Circle2D)
	{
		mSize = Vector2::Zero;
		mOffset = Vector2::Zero;
	}
	CircleCollider2D::~CircleCollider2D()
	{
	}
	void CircleCollider2D::Initialize()
	{
	}
	void CircleCollider2D::Update()
	{
	}
	void CircleCollider2D::LateUpdate()
	{
	}
	void CircleCollider2D::Render(HDC hdc)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		if (renderer::mainCamera)
			pos = renderer::mainCamera->CalculatePosition(pos);
		Vector2 offset = GetOffset();
		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);
		HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, greenPen);

		Vector2 rightBottom;
		rightBottom.x = pos.x + offset.x + mSize.x;
		rightBottom.y = pos.y + offset.y + mSize.y;
		Ellipse(hdc, pos.x + offset.x
			, pos.y + offset.y
			, rightBottom.x
			, rightBottom.y);
		SelectObject(hdc, oldBrush);
		SelectObject(hdc, oldPen);
		DeleteObject(greenPen);
	}
}
