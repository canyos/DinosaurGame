#include "pPlayerScript.h"
#include "pInput.h"
#include "pTime.h"
#include "pTransform.h"
#include "pGameObject.h"
#include "pAnimator.h"
#include "pCat.h"
#include "pCatScript.h"
#include "pObject.h"
#include "pResources.h"
#include "pCollider.h"
#include "pRigidBody.h"
#include "pUIManager.h"
namespace p {
	PlayerScript::PlayerScript()
		: mState(PlayerScript::eState::Idle)
		, mAnimator(nullptr)
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{


	}
	void PlayerScript::Update()
	{
		if (mAnimator == nullptr)
		{
			mAnimator = GetOwner()->GetComponent<Animator>();
		}

		switch (mState)
		{
		case p::PlayerScript::eState::Idle:
			idle();
			break;
		case p::PlayerScript::eState::Walk:
			move();
			break;

		case p::PlayerScript::eState::Sleep:
			break;
		case p::PlayerScript::eState::Attack:
			break;
		case p::PlayerScript::eState::GiveWater:
			giveWater();
			break;
		default:
			break;
		}
		//�ȼ� �浹
		/*Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		COLORREF color = mPixelMap->GetPixel(pos.x, pos.y+50);
		RigidBody* rb = GetOwner()->GetComponent<RigidBody>();
		if (color == RGB(255, 0, 0)) {
		
			rb->SetGround(true);
			pos.y -= 3;
			tr->SetPosition(pos);
		}
		else {
			
			rb->SetGround(false);
		}*/
	}
	void PlayerScript::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		if (pos.y > 750) pos.y = 600;
		tr->SetPosition(pos);
	}
	void PlayerScript::Render(HDC hdc)
	{
	}

	void PlayerScript::AttackEffect()
	{
		
	}

	void PlayerScript::idle()
	{
		//if (Input::GetKey(eKeyCode::D))
		//{
		//	mState = PlayerScript::eState::Walk;
		//	//mAnimator->PlayAnimation(L"RightWalk");
		//}
		//if (Input::GetKey(eKeyCode::A)) {
		//	mState = PlayerScript::eState::Walk;
		//	//mAnimator->PlayAnimation(L"LeftWalk");
		//}
			
		if (Input::GetKey(eKeyCode::W)) {
			mState = PlayerScript::eState::Walk;
			//mAnimator->PlayAnimation(L"UpWalk");
		}
			
		//if (Input::GetKey(eKeyCode::S)) {
		//	mState = PlayerScript::eState::Walk;
		//	//mAnimator->PlayAnimation(L"DownWalk");
		//}			
	}

	void PlayerScript::move()
	{

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		RigidBody* rb = GetOwner()->GetComponent<RigidBody>();

		if (Input::GetKey(eKeyCode::D))
		{
			//pos.x += 100.0f * Time::DeltaTime();
			rb->AddForce(Vector2(200.0f, 0.0f));
		}
		if (Input::GetKey(eKeyCode::A))
		{
			//pos.x -= 100.0f * Time::DeltaTime();
			rb->AddForce(Vector2(-200.0f, 0.0f));
		}
		if (Input::GetKey(eKeyCode::W))
		{
			if (rb->GetGround() == true) {
				//pos.y -= 100.0f * Time::DeltaTime();
				//rb->AddForce(Vector2(0, -200.0f));
				Vector2 velocity = rb->GetVelocity();
				velocity.y = -700.0f;
				rb->SetVelocity(velocity);
				rb->SetGround(false);
			}
			
		}

		//if (Input::GetKey(eKeyCode::S))
		//{
		//	//pos.y += 100.0f * Time::DeltaTime();
		//	rb->AddForce(Vector2(0.0f, 200.0f));
		//}

		//tr->SetPosition(pos);

		if (Input::GetKeyUp(eKeyCode::D) || Input::GetKeyUp(eKeyCode::A)
			|| Input::GetKeyUp(eKeyCode::W) || Input::GetKeyUp(eKeyCode::S))
		{
			mState = PlayerScript::eState::Idle;
			mAnimator->PlayAnimation(L"SitDown", false);
		}
	}
	void PlayerScript::giveWater()
	{
		if (mAnimator->IsComplete()) {
			mState = eState::Idle;
			mAnimator->PlayAnimation(L"Idle", false);
		}
	}
}

