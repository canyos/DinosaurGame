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
		int score;
		int HighScore;
		HFONT hFont;

		std::wstring cactusName[3] = { L"Cactus A", L"Cactus B", L"Cactus C" };
		int spawnTime = 0;
		int spawnInterval = 1;

		std::wstring cloudName[2] = { L"Cloud A", L"Cloud B" };
		int cloudTime = 0;
		int cloudInterval = 20;

		std::wstring rockName[2] = { L"Rock A", L"Rock B" };
		int rockTime = 0;
		int rockInterval = 40;

		
	};
}

