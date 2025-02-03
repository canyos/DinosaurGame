#pragma once
#include "pSceneManager.h"
#include "pPlayScene.h"
#include "pTitleScene.h"
#include "pToolScene.h"
namespace p {
	void LoadScenes() {
<<<<<<< HEAD
		//SceneManager::CreateScene<TitleScene>(L"TitleScene");
		//SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<ToolScene>(L"ToolScene");

		//SceneManager::LoadScene(L"PlayScene");
		SceneManager::LoadScene(L"ToolScene");
=======
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		//SceneManager::CreateScene<ToolScene>(L"ToolScene");

		SceneManager::LoadScene(L"TitleScene");
		//SceneManager::LoadScene(L"PlayScene");
		//SceneManager::LoadScene(L"ToolScene");
>>>>>>> 7d708bcf8f26f030c51553dadcc318b9311888d5
	}
}
