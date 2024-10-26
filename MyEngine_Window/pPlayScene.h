#pragma once
#include "../MyEngin_Source/pScene.h"

namespace p {
	class PlayScene: public Scene
	{
	public:
		PlayScene();
		~PlayScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void OnEnter() override;
		void OnExit() override;

		
	private:
		class Player* mPlayer;
		class Cactus* mCactus[3];
		int time = 0;
		int spawnTime = 1;
		
	};
}

