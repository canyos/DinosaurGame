#pragma once
#include "pScript.h"
#include "pTexture.h"
namespace p {
	class PlayerScript : public Script
	{
	public:
		enum class eState {
			Idle,
			Walk,
			Sleep,
			Attack,
			GiveWater,
		};
		PlayerScript();
		~PlayerScript();

		void Initialize()override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC hdc)override;

		void AttackEffect();

		void SetPixelMapTexture(graphics::Texture* texture) { mPixelMap = texture; }
	private:
		void idle();
		void move();
		void giveWater();
	private:
		eState mState;
		class Animator* mAnimator;
		graphics::Texture* mPixelMap;
	};
}


