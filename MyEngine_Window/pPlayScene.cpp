#include "pPlayScene.h"
#include "pGameObject.h"
#include "pPlayer.h"
#include "pTransform.h"
#include "pSpriteRenderer.h"
#include "pInput.h"
#include "pTitleScene.h"
#include "pSceneManager.h"
#include "pObject.h"
#include "pTexture.h"
#include "pResources.h"
#include "pPlayerScript.h"
#include "pCamera.h"
#include "pRenderer.h"
#include "pAnimator.h"
#include "pCat.h"
#include "pCatScript.h"
#include "pBoxCollider2D.h"
#include "pCollisionManager.h"
#include "pTile.h"
#include "pTilemapRenderer.h"
#include "pRigidBody.h"
#include "pFloor.h"
#include "pFloorScript.h"
#include "pUIManager.h"
#include "pAudioClip.h"
#include "pAudioListener.h"
#include "pAudioSource.h"
#include "pCactus.h"
#include "pCactusScript.h"
#include <random>

namespace p
{
	PlayScene::PlayScene()
		
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		
		/*FILE* pFile = nullptr;
		_wfopen_s(&pFile, L"../Resources/test", L"rb");
		while (true)
		{
			int idxX = 0;
			int idxY = 0;

			int posX = 0;
			int posY = 0;

			if (fread(&idxX, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&idxY, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&posX, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&posY, sizeof(int), 1, pFile) == NULL)
				break;

			Tile* tile = object::Instantiate<Tile>(eLayerType::Tile, Vector2(posX, posY));
			TilemapRenderer* tmr = tile->AddComponent<TilemapRenderer>();
			tmr->SetTexture(Resources::Find<graphics::Texture>(L"SpringFloor"));
			tmr->SetIndex(Vector2(idxX, idxY));

			//mTiles.push_back(tile);
		}
		fclose(pFile);*/
		
		//main camera
		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(344.0f, 442.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		renderer::mainCamera = cameraComp;
		//camera->AddComponent<PlayerScript>();


		mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);
		//object::DontDestroyOnLoad(mPlayer);
		mPlayer->AddComponent<AudioListener>();

		PlayerScript* plScript = mPlayer->AddComponent<PlayerScript>();
		BoxCollider2D* collider = mPlayer->AddComponent<BoxCollider2D>();
		collider->SetSize(Vector2(0.9f, 0.8f));
		collider->SetOffset(Vector2(0.0f, 0.0f));

		graphics::Texture* playerTex = Resources::Find<graphics::Texture>(L"Player");
		Animator* playerAnimator = mPlayer->AddComponent<Animator>();
		playerAnimator->CreateAnimation(L"run", playerTex
			, Vector2(0.0f, 0.0f), Vector2(16.9f, 16.0f), Vector2(1.0f,0.0f), 4, 0.1f);
		playerAnimator->CreateAnimation(L"die", playerTex
			, Vector2(16.9f * 4, 0.0f), Vector2(16.9f, 16.0f), Vector2(1.0f, 0.0f), 2, 0.5f);


		//playerAnimator->GetCompleteEvent(L"FrontGiveWater") = std::bind(&PlayerScript::AttackEffect, plScript);


		mPlayer->GetComponent<Transform>()->SetPosition(Vector2(100.0f, 600.0f));
		mPlayer->GetComponent<Transform>()->SetRotation(0.0f);
		mPlayer->GetComponent<Transform>()->SetScale(Vector2(6.0f, 6.0f));
		playerAnimator->PlayAnimation(L"run", true);
		mPlayer->AddComponent<RigidBody>();
		


		Floor* floor = object::Instantiate<Floor>(eLayerType::Floor, Vector2(0.0f, 700.0f));
		floor->SetName(L"Floor");
		//SpriteRenderer* floorSr = floor->AddComponent<SpriteRenderer>();
		//floorSr->SetTexture(Resources::Find<graphics::Texture>(L"PixelMap"));

		//AudioSource* as = floor->AddComponent<AudioSource>();

		BoxCollider2D* floorCol = floor->AddComponent<BoxCollider2D>();
		floorCol->SetSize(Vector2(1600.0f, 200.0f));
		floor->AddComponent<FloorScript>();

		/*AudioClip* ac = Resources::Load<AudioClip>(L"BGSound", L"..\\Resources\\smw_bonus_game_end.wav");
		as->SetClip(ac);
		as->Play();*/

		plScript->SetPixelMapTexture(Resources::Find<graphics::Texture>(L"PixelMap"));

		/*///CAT
		Cat* cat = object::Instantiate<Cat>(enums::eLayerType::Animal);
		cat->AddComponent<CatScript>();
		graphics::Texture* catTex = Resources::Find<graphics::Texture>(L"Cat");
		Animator* catAnimator = cat->AddComponent<Animator>(); 
		BoxCollider2D* boxCatCollider = cat->AddComponent<BoxCollider2D>();
		boxCatCollider->SetOffset(Vector2(-50.0f, -50.0f));
		catAnimator->CreateAnimationByFolder(L"MushroomIdle", L"..\\Resources\\Mushroom", Vector2::Zero, 0.1f);
		catAnimator->PlayAnimation(L"MushroomIdle", true);
		cat->GetComponent<Transform>()->SetPosition(Vector2(360.0f, 420.0f));



		//GameObject* sheet = object::Instantiate<GameObject>(enums::eLayerType::Particle);
		//SpriteRenderer* sheetSR = sheet->AddComponent<SpriteRenderer>();


		//graphcis::Texture* mrIdle = Resources::Find<graphcis::Texture>(L"MushroomIdle");
		//sheetSR->SetTexture(mrIdle);
		//Animator* playerAnimator = mPlayer->AddComponent<Animator>();*/

		// 게임 오브젝트 생성후에 레이어와 게임오브젝트들의 init함수를 호출
		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		Scene::Update();
		time++;
		std::wstring strs[3] = { L"Cactus A", L"Cactus B", L"Cactus C" };
		
		if (time % spawnTime == 0) {
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_int_distribution<int> cactus(0, 2);
			auto randNum = cactus(mt);
			mCactus[randNum] = object::Instantiate<Cactus>(enums::eLayerType::Animal);
			graphics::Texture* cactusATexture = Resources::Find<graphics::Texture>(strs[randNum]);
			BoxCollider2D* cactusCollider = mCactus[randNum]->AddComponent<BoxCollider2D>();

			SpriteRenderer* cactusSr = mCactus[randNum]->AddComponent<SpriteRenderer>();
			cactusSr->SetTexture(cactusATexture);
			Transform* cacTr = mCactus[randNum]->AddComponent<Transform>();
			mCactus[randNum]->AddComponent<CactusScript>();
			
			if (randNum == 0) {
				cactusATexture->SetWidth(12);
				cactusATexture->SetHeight(20);
				cacTr->SetPosition(Vector2(1600.0f, 620.0f));
				cacTr->SetScale(Vector2(3.0f, 4.0f));
				cactusCollider->SetSize(Vector2(0.36f, 0.8f));
				cactusCollider->SetOffset(Vector2::Zero);
			}
			else if (randNum == 1) {
				cactusATexture->SetWidth(21);
				cactusATexture->SetHeight(15);
				cacTr->SetPosition(Vector2(1600.0f, 610.0f));
				cacTr->SetScale(Vector2(3.0f, 6.0f));
				cactusCollider->SetSize(Vector2(0.63f, 0.9f));
				cactusCollider->SetOffset(Vector2::Zero);
			}
			else {
				cactusATexture->SetWidth(28);
				cactusATexture->SetHeight(20);
				cacTr->SetPosition(Vector2(1600.0f, 600.0f));
				cacTr->SetScale(Vector2(3.0f, 5.0f));
				cactusCollider->SetSize(Vector2(0.84f, 1.0f));
				cactusCollider->SetOffset(Vector2::Zero);
			}
			
			
			std::uniform_int_distribution<int> randSpawnTime(700, 1000);
			spawnTime = randSpawnTime(mt);
			time = 0;
		}
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
		
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		/*wchar_t str[50] = L"Play Scene";
		TextOutW(hdc, 0, 0, str, lstrlenW(str));*/
	}
	void PlayScene::OnEnter()
	{
		Scene::OnEnter();

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Animal, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
	}
	void PlayScene::OnExit()
	{
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Animal, false);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Floor, false);
		Scene::OnExit();
	}
}