#pragma once
#include "pScript.h"
#include "pTransform.h"
namespace p {
	class CatScript : public Script
	{
	public:
		enum class eState {
			SitDown,
			Walk,
			Sleep,
			Attack,
			LayDown,
		};
		enum class eDirection {
			Left,
			Right,
			Down,
			Up,
			End,
		};
		CatScript();
		~CatScript();
		Vector2 mDest;
		void Initialize()override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC hdc)override;
		void SetPlayer(GameObject* player) { mPlayer = player; }
	private:
		void idle();
		void move();
		void PlayWalkAnimationByDirection(eDirection direction);
		void translate(Transform* tr);
		void layDown();
		
		
	private:
		eState mState;
		class Animator* mAnimator;
		float mTime;
		eDirection mDirection;
		float mDeathTime;

		GameObject* mPlayer;
		float mRadian;
		
	};
}
