#pragma once
#include "pGameObject.h"

namespace p {
	class Particle : public GameObject
	{
	public:
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		float GetSpeed() { return mSpeed; }
		void SetSpeed(float speed) { mSpeed = speed; }
	private:
		float mSpeed;
	};
}