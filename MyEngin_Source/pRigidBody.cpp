#include "pRigidBody.h"
#include "pTime.h"
#include "pTransform.h"
#include "pGameObject.h"
namespace p {
	RigidBody::RigidBody()
		:Component(enums::eComponentType::RigidBody),
		mMass(1.0f), 
		mbGround(false),
		mFriction(10.0f),
		mVelocity(Vector2::Zero),
		mForce(Vector2::Zero),
		mLimitedVelocity(Vector2(200.0f,1000.0f)),
		mGravity(Vector2(0.0f,800.0f)),
		mAcceleration(Vector2::Zero)
	{
	}
	RigidBody::~RigidBody()
	{
	}
	void RigidBody::Initialize()
	{
	}
	void RigidBody::Update()
	{
		//f = ma
		mAcceleration = mForce / mMass;
		//속도에 가속도 더함
		mVelocity += mAcceleration * Time::DeltaTime();
		if (mbGround) {
			//땅위에있음
			Vector2 gravity = mGravity;
			gravity.normalize();

			float dot = Vector2::Dot(mVelocity, gravity);//중력과 방향의 내적해 이동할 방향
			mVelocity -= gravity * dot;
		}
		else {
			//공중에있음
			mVelocity += mGravity * Time::DeltaTime();
		}

		//최대 속도 제한
		Vector2 gravity = mGravity;
		gravity.normalize();
		float dot = Vector2::Dot(mVelocity, gravity);
		gravity = gravity * dot;

		Vector2 sideVelocity = mVelocity - gravity;
		if (mLimitedVelocity.y < gravity.length()) {
			gravity.normalize();
			gravity *= mLimitedVelocity.y;
		}
		if (mLimitedVelocity.x < sideVelocity.length()) {
			sideVelocity.normalize();
			sideVelocity *= mLimitedVelocity.x;
		}
		
		mVelocity = gravity + sideVelocity;

		if (!(mVelocity == Vector2::Zero)) {
			Vector2 friction = -mVelocity;
			friction = friction.normalize()*mFriction*mMass*Time::DeltaTime();
			//마찰력으로 인한 속도 감소량이 현재속도보다 크면 안움직임
			if (mVelocity.length() <= friction.length()) {
				mVelocity = Vector2::Zero;
			}
			else {
				mVelocity += friction;
			}
		}
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		pos = pos + mVelocity * Time::DeltaTime();
		tr->SetPosition(pos);

		mForce.clear();
	}
	void RigidBody::LateUpdate()
	{
	}
	void RigidBody::Render(HDC hdc)
	{
	}
}

