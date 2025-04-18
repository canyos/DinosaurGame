#include "pCameraScript.h"
#include "pInput.h"
#include "pTime.h"
#include "pTransform.h"
#include "pGameObject.h"
#include "pAnimator.h"
#include "pCatScript.h"
#include "pObject.h"
#include "pResources.h"
#include "pCollider.h"

namespace p {
	CameraScript::CameraScript()
	{

	}
	CameraScript::~CameraScript()
	{
	}
	void CameraScript::Initialize()
	{
	}
	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::D))
		{
			pos.x = min(4010.0f, pos.x + 500.0f * Time::DeltaTime());
		}
		if (Input::GetKey(eKeyCode::A))
		{
			pos.x =  max(800.0f, pos.x - 500.0f * Time::DeltaTime());
		}
		//if (Input::GetKey(eKeyCode::Up))
		//{
		//	pos.y -= 100.0f * Time::DeltaTime();
		//}
		//if (Input::GetKey(eKeyCode::Down))
		//{
		//	pos.y += 100.0f * Time::DeltaTime();
		//}

		tr->SetPosition(pos);
	}
	void CameraScript::LateUpdate()
	{
	}
	void CameraScript::Render(HDC hdc)
	{
	}
}
