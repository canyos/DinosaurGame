#pragma once
#include "pComponent.h"

namespace p {
	class RigidBody : public Component
	{
	public:
		RigidBody();
		~RigidBody();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		void SetMass(float mass) { mMass = mass; }
		void AddForce(Vector2 force) { mForce = force; }
		void SetGround(bool ground) { mbGround = ground; }
		bool GetGround() { return mbGround; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		Vector2 GetVelocity() { return mVelocity; }
	private:
		bool mbGround;//¶¥¿¡ ´ê¾Ò³Ä
		float mMass;
		float mFriction;//¸¶Âû·Â
		Vector2 mForce;//Èû
		Vector2 mAcceleration;
		Vector2 mVelocity;//¼Óµµ
		Vector2 mLimitedVelocity;//¼Óµµ
		Vector2 mGravity;//Áß·Â
	};
}
