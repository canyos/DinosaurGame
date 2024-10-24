#pragma once
#include "pScene.h"

namespace p {
	class DontDestroyOnLoad : public Scene {
	public:
		DontDestroyOnLoad();
		~DontDestroyOnLoad();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
		
		void OnEnter()override;//Scene에 들어가거나 
		void OnExit()override;//나갈때 필요없는거 처리


	private:
	};
}


