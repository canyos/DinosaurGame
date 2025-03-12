#include "pToolScene.h"
#include "pObject.h"
#include "pTile.h"
#include "pTilemapRenderer.h"
#include "pResources.h"
#include "pTexture.h"
#include "pCamera.h"
#include "pRenderer.h"
#include "pInput.h"
#include "pCameraScript.h"
#include "pBackGround.h"
#include "pSpriteRenderer.h"

namespace p
{
	ToolScene::ToolScene()
	{
	}
	ToolScene::~ToolScene()
	{
	}
	void ToolScene::Initialize()
	{
		TILE_LEN = 100;
		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(800.0f, 450.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();
		renderer::mainCamera = cameraComp;
		
		BackGround* bg1 = object::Instantiate<BackGround>(eLayerType::BackGround, Vector2(0.0f, 0.0f));
		bg1->SetName(L"Sky");
		SpriteRenderer* bgSr1 = bg1->AddComponent<SpriteRenderer>();
		graphics::Texture* skyTexture = Resources::Find<graphics::Texture>(L"Sky");
		bgSr1->SetTexture(skyTexture);
		bgSr1->SetSize(Vector2(34.0f, 11.0f));


		BackGround* bg2 = object::Instantiate<BackGround>(eLayerType::BackGround, Vector2(0.0f , 700.0f));
		bg2->SetName(L"ground");
		SpriteRenderer* bgSr2 = bg2->AddComponent<SpriteRenderer>();
		graphics::Texture* groundTexture = Resources::Find<graphics::Texture>(L"Ground");
		bgSr2->SetTexture(groundTexture);
		bgSr2->SetSize(Vector2(34.0f, 4.2f));
		

		/*Tile* tile = object::Instantiate<Tile>(eLayerType::Tile);
		TilemapRenderer* tmr = tile->AddComponent<TilemapRenderer>();
		tmr->SetTexture(Resources::Find<graphics::Texture>(L"SpringFloor"));*/

		Scene::Initialize();
	}
	void ToolScene::Update()
	{
		Scene::Update();
	}
	void ToolScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (Input::GetKeyDown(eKeyCode::LButton))
		{
			Vector2 pos = Input::GetMousePosition();
			pos = renderer::mainCamera->CalculateTilePosition(pos);

			if (pos.x >= 0.0f && pos.y >= 0.0f)
			{
				int idxX = pos.x / TilemapRenderer::TileSize.x;
				int idxY = pos.y / TilemapRenderer::TileSize.y;

				Tile* tile = object::Instantiate<Tile>(eLayerType::Tile);
				TilemapRenderer* tmr = tile->AddComponent<TilemapRenderer>();
				tmr->SetTexture(Resources::Find<graphics::Texture>(L"SpringFloor"));
				tmr->SetIndex(TilemapRenderer::SelectedIndex);

				tile->SetIndexPosition(idxX, idxY);
				mTiles.push_back(tile);
			}
			else
			{
				//
			}
		}
		if (Input::GetKeyDown(eKeyCode::S)) {
			Save();
		}
		if (Input::GetKeyDown(eKeyCode::L))
		{
			Load();
		}
	}
	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		
		for (size_t i = 0; i < 100; i++)
		{
			Vector2 pos = renderer::mainCamera->CalculatePosition(Vector2(TilemapRenderer::TileSize.x * i, 0.0f));

			MoveToEx(hdc, pos.x, 0, NULL);
			LineTo(hdc, pos.x, 1600);
		}

		for (size_t i = 0; i < 60; i++)
		{
			Vector2 pos = renderer::mainCamera->CalculatePosition
			(
				Vector2(0.0f, TilemapRenderer::TileSize.y * i)
			);

			MoveToEx(hdc, 0, pos.y, NULL);
			LineTo(hdc, 1600, pos.y);
		}
	}
	void ToolScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void ToolScene::OnExit()
	{
		Scene::OnExit();
	}
	void ToolScene::Save()
	{
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {0};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		
		if (!GetSaveFileName(&ofn))
			return;

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"a+");
		

		int* arr = new int [TILE_LEN];
		memset(arr, 0, sizeof(int)*TILE_LEN);
		for (Tile* tile : mTiles)
		{
			//TilemapRenderer* tmr = tile->GetComponent<TilemapRenderer>();
			Transform* tr = tile->GetComponent<Transform>();

			//Vector2 sourceIndex = tmr->GetIndex();
			Vector2 position = tr->GetPosition();
			arr[(int)(position.x/TilemapRenderer::TileSize.x)]++;
		}

		for (int i = 0; i < TILE_LEN; i++) {
			fwrite(&arr[i], sizeof(int), 1, pFile);
		}
		
		fclose(pFile);
	}
	void ToolScene::Load()
	{
		for (Tile* tile : mTiles) {
			tile->Death();
		}
		mTiles = {};
		OPENFILENAME ofn = {};
		wchar_t  szFilePath[256] = { 0 };
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		if (false == GetOpenFileName(&ofn))
			return;

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"r+");
		for(int i=0;i< TILE_LEN;i++)
		{
			int height = 0;
			if (fread(&height, sizeof(int), 1, pFile) == NULL)
				break;
			
			for (int j = 0; j < height;j++) {
				Tile* tile = object::Instantiate<Tile>(eLayerType::Tile, Vector2(i*TilemapRenderer::TileSize.x, (13-j)*TilemapRenderer::TileSize.y));
				TilemapRenderer* tmr = tile->AddComponent<TilemapRenderer>();
				tmr->SetTexture(Resources::Find<graphics::Texture>(L"SpringFloor"));
				tmr->SetIndex(Vector2(0, 1));

				mTiles.push_back(tile);
			}

		}
		fclose(pFile);
	}
}

LRESULT CALLBACK WndTileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		//int wmId = LOWORD(wParam);
		//// 메뉴 선택을 구문 분석합니다:
		//switch (wmId)
		//{
		//case IDM_ABOUT:
		//	DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		//	break;
		//case IDM_EXIT:
		//	DestroyWindow(hWnd);
		//	break;
		//default:
		//	return DefWindowProc(hWnd, message, wParam, lParam);
		//}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		p::graphics::Texture* texture =
			p::Resources::Find<p::graphics::Texture>(L"SpringFloor");
		TransparentBlt(hdc
			, 0, 0
			, texture->GetWidth()
			, texture->GetHeight()
			, texture->GetHdc()
			, 0, 0
			, texture->GetWidth()
			, texture->GetHeight()
			, RGB(255, 0, 255));

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_LBUTTONDOWN:
	{
		POINT mousePos = { };
		GetCursorPos(&mousePos);
		ScreenToClient(hWnd, &mousePos);
		p::math::Vector2 mousePosition;
		mousePosition.x = mousePos.x;
		mousePosition.y = mousePos.y;
		int idxX = mousePosition.x / 1.0f;
		int idxY = mousePosition.y / 1.0f;
		p::TilemapRenderer::SelectedIndex = Vector2(idxX, idxY);
	}
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}