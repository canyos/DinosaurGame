#pragma once
#include "pScript.h"
#include "pTransform.h"
namespace p {
	class ParticleScript : public Script
	{
	public:
		ParticleScript();
		~ParticleScript();

		void Initialize()override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC hdc)override;

	private:


	private:

	};
}
