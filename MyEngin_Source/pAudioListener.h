#pragma once
#include "pComponent.h"

namespace p {
	class AudioListener : public Component
	{
	public:
		AudioListener();
		~AudioListener();
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
	};

}


