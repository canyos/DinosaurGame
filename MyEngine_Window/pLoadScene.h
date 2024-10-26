#pragma once
#include "pSceneManager.h"
#include "pPlayScene.h"
#include "pTitleScene.h"
#include "pToolScene.h"
namespace p {
	void LoadScenes() {
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		//SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		
		//SceneManager::LoadScene(L"PlayScene");
		SceneManager::LoadScene(L"PlayScene");
	}
}
