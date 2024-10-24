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
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		COLORREF color = mPixelMap->GetPixel(pos.x, pos.y+50);
		RigidBody* rb = GetOwner()->GetComponent<RigidBody>();
		if (color == RGB(255, 0, 0)) {
		
			rb->SetGround(true);
			pos.y -= 1;
			tr->SetPosition(pos);
		}
		else {
			
			rb->SetGround(false);
		}
	}
	void PlayerScript::LateUpdate()
	{
	}
	void PlayerScript::Render(HDC hdc)
	{
	}

	void PlayerScript::AttackEffect()
	{
		
	}

	void PlayerScript::OnCollisionEnter(Collider * other)
	{
	}

	void PlayerScript::OnCollisionStay(Collider * other)
	{
	}

	void PlayerScript::OnCollisionExit(Collider * other)
	{
	}

	void PlayerScript::idle()
	{
		if (Input::GetKey(eKeyCode::LButton)) {
			//mState = PlayerScript::eState::GiveWater;
			//mAnimator->PlayAnimation(L"FrontGiveWater",false);
			//Vector2 mousePos = Input::GetMousePosition();

			Cat* cat = object::Instantiate<Cat>(enums::eLayerType::Animal);
			CatScript* catSrc = cat->AddComponent<CatScript>();
			catSrc->SetPlayer(GetOwner());

			graphics::Texture* catTexture = Resources::Find<graphics::Texture>(L"cat");;
			Animator* catAnimator = cat->AddComponent<Animator>();
			catAnimator->CreateAnimation(L"DownWalk", catTexture
				, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			catAnimator->CreateAnimation(L"RightWalk", catTexture
				, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			catAnimator->CreateAnimation(L"UpWalk", catTexture
				, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			catAnimator->CreateAnimation(L"LeftWalk", catTexture
				, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			catAnimator->CreateAnimation(L"SitDown", catTexture
				, Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			catAnimator->CreateAnimation(L"Grooming", catTexture
				, Vector2(0.0f, 160.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			catAnimator->CreateAnimation(L"LayDown", catTexture
				, Vector2(0.0f, 192.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			catAnimator->PlayAnimation(L"SitDown", false);

			Transform* tr = GetOwner()->GetComponent<Transform>();
			cat->GetComponent<Transform>()->SetPosition(tr->GetPosition());
			cat->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));

			Vector2 mousePos = Input::GetMousePosition();
			catSrc->mDest = mousePos;
		}

		if (Input::GetKey(eKeyCode::D))
		{
			mState = PlayerScript::eState::Walk;
			//mAnimator->PlayAnimation(L"RightWalk");
		}
		if (Input::GetKey(eKeyCode::A)) {
			mState = PlayerScript::eState::Walk;
			//mAnimator->PlayAnimation(L"LeftWalk");
		}
			
		if (Input::GetKey(eKeyCode::W)) {
			mState = PlayerScript::eState::Walk;
			//mAnimator->PlayAnimation(L"UpWalk");
		}
			
		if (Input::GetKey(eKeyCode::S)) {
			mState = PlayerScript::eState::Walk;
			//mAnimator->PlayAnimation(L"DownWalk");
		}
		if (Input::GetKeyDown(eKeyCode::I))
		{
			UIManager::Push(eUIType::HpBar);
			//UIManager::Push(eUIType::Button);
		}
		if (Input::GetKeyDown(eKeyCode::O))
		{
			UIManager::Pop(eUIType::HpBar);
		}
			
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
				velocity.y = -500.0f;
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

