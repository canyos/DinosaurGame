#include "pTitleScene.h"
#include "pInput.h"
#include "pSceneManager.h"
#include "pPlayScene.h"
#include "pUIManager.h"
#include "pUIButton.h"


namespace p
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		Scene::Initialize();
	}

	void TitleScene::Update()
	{
		Scene::Update();
	}
	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();
		Scene::LateUpdate();
		if (Input::GetKeyDown(eKeyCode::N)) {
			SceneManager::LoadScene(L"PlayScene");
		}
	}
	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		Vector2 mousePos = Input::GetMousePosition();
		wchar_t str[50] = L"Title  Scene";
		TextOutW(hdc, 0, 0, str, lstrlenW(str));

		int len = wcsnlen_s(str, 50);

		swprintf_s(str, 50, L"mouse x : %f ", mousePos.x);
		len = wcsnlen_s(str, 50);
		TextOutW(hdc, 0, 10, str, len);

		swprintf_s(str, 50, L"mouse y : %f ", mousePos.y);
		len = wcsnlen_s(str, 50);
		TextOutW(hdc, 0, 30, str, len);

	}
	void TitleScene::OnEnter()
	{
		UIManager::Push(L"Start Button");
		UIManager::Push(L"Exit Button");
	}
	void TitleScene::OnExit()
	{
		UIManager::Pop(L"Start Button");
		UIManager::Pop(L"Exit Button");
	}
}