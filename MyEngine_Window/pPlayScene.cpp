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
#include "pBoxCollider2D.h"
#include "pCollisionManager.h"
#include "pRigidBody.h"
#include "pFloor.h"
#include "pFloorScript.h"
#include "pUIManager.h"
#include "pCactus.h"
#include "pCactusScript.h"
#include <random>
#include "pBackGround.h"
#include "pParticle.h"
#include "pParticleScript.h"
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
		//mPlayer->AddComponent<AudioListener>();

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
		
		//픽셀충돌
		/*SpriteRenderer* floorSr = floor->AddComponent<SpriteRenderer>();
		//floorSr->SetTexture(Resources::Find<graphics::Texture>(L"PixelMap"));
		//plScript->SetPixelMapTexture(Resources::Find<graphics::Texture>(L"PixelMap"));*/
		
		Floor* floor = object::Instantiate<Floor>(eLayerType::Floor, Vector2(0.0f, 700.0f));
		floor->SetName(L"Floor");
		BoxCollider2D* floorCol = floor->AddComponent<BoxCollider2D>();
		floorCol->SetSize(Vector2(1600.0f, 200.0f));
		floor->AddComponent<FloorScript>();
		

		BackGround* bg1 = object::Instantiate<BackGround>(eLayerType::BackGround, Vector2(0.0f, 0.0f));
		bg1->SetName(L"Sky");
		SpriteRenderer* bgSr1 = bg1->AddComponent<SpriteRenderer>();
		graphics::Texture* skyTexture = Resources::Find<graphics::Texture>(L"Sky");
		bgSr1->SetTexture(skyTexture);
		bgSr1->SetSize(Vector2(34.0f,11.0f));

		BackGround* bg2 = object::Instantiate<BackGround>(eLayerType::BackGround, Vector2(0.0f, 700.0f));
		bg2->SetName(L"ground");
		SpriteRenderer* bgSr2 = bg2->AddComponent<SpriteRenderer>();
		graphics::Texture* groundTexture = Resources::Find<graphics::Texture>(L"Ground");
		bgSr2->SetTexture(groundTexture);
		bgSr2->SetSize(Vector2(34.0f, 4.2f));

		//오디오 재생
		/*AudioSource* as = floor->AddComponent<AudioSource>();
		AudioClip* ac = Resources::Load<AudioClip>(L"BGSound", L"..\\Resources\\smw_bonus_game_end.wav");
		as->SetClip(ac);
		as->Play();*/

		// 게임 오브젝트 생성후에 레이어와 게임오브젝트들의 init함수를 호출
		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		Scene::Update();

		if (isEnd)
			return;
		spawnTime++;
		cloudTime++;
		rockTime++;

		if (spawnTime % spawnInterval == 0) {
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_int_distribution<int> cactusRand(0, 2);
			auto randNum = cactusRand(mt);

			Cactus* cactus = object::Instantiate<Cactus>(enums::eLayerType::Animal);
			graphics::Texture* cactusATexture = Resources::Find<graphics::Texture>(cactusName[randNum]);
			BoxCollider2D* cactusCollider = cactus->AddComponent<BoxCollider2D>();

			SpriteRenderer* cactusSr = cactus->AddComponent<SpriteRenderer>();
			cactusSr->SetTexture(cactusATexture);
			Transform* cacTr = cactus->AddComponent<Transform>();
			cactus->AddComponent<CactusScript>();
			
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
			
			std::uniform_int_distribution<int> randSpawnInterval(30, 50);
			spawnInterval = randSpawnInterval(mt);
			spawnTime = 0;
		}
		
		if (cloudTime % cloudInterval == 0) {
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_int_distribution<int> cloudRand(0, 500);
			auto randNum = cloudRand(mt);

			Particle* cloud = object::Instantiate<Particle>(enums::eLayerType::Particle);
			cloud->SetSpeed(150.0f);
			graphics::Texture* cloudTexture = Resources::Find<graphics::Texture>(cloudName[randNum%2]);

			SpriteRenderer* cloudSr = cloud->AddComponent<SpriteRenderer>();
			cloudSr->SetTexture(cloudTexture);
			Transform* cloudTr = cloud->AddComponent<Transform>();
			cloud->AddComponent<ParticleScript>();

			if (randNum%2 == 0) {
				cloudTexture->SetWidth(20);
				cloudTexture->SetHeight(11);
				cloudTr->SetPosition(Vector2(1600.0f, randNum));
				cloudTr->SetScale(Vector2(2.0f, 2.0f));
			}
			else if (randNum%2 == 1) {
				cloudTexture->SetWidth(11);
				cloudTexture->SetHeight(5);
				cloudTr->SetPosition(Vector2(1600.0f, randNum));
				cloudTr->SetScale(Vector2(4.0f, 4.0f));
			}

			std::uniform_int_distribution<int> randSpawnInterval(30, 50);
			cloudInterval = randSpawnInterval(mt);
			cloudTime = 0;
		}

		if (rockTime % rockInterval == 0) {
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_int_distribution<int> rockRand(700, 800);
			auto randNum = rockRand(mt);

			Particle* rock = object::Instantiate<Particle>(enums::eLayerType::Particle);
			rock->SetSpeed(350.0f);
			graphics::Texture* rockTexture = Resources::Find<graphics::Texture>(rockName[randNum % 2]);

			SpriteRenderer* rockSr = rock->AddComponent<SpriteRenderer>();
			rockSr->SetTexture(rockTexture);
			Transform* rockTr = rock->AddComponent<Transform>();
			rock->AddComponent<ParticleScript>();

			if (randNum % 2 == 0) {
				rockTexture->SetWidth(48);
				rockTexture->SetHeight(24);
				rockTr->SetPosition(Vector2(1600.0f, randNum));
				rockTr->SetScale(Vector2(2.0f, 4.0f));
			}

			else if (randNum % 2 == 1) {
				rockTexture->SetWidth(16);
				rockTexture->SetHeight(16);
				rockTr->SetPosition(Vector2(1600.0f, randNum));
				rockTr->SetScale(Vector2(6.0f, 6.0f));
			}

			std::uniform_int_distribution<int> randSpawnInterval(30, 50);
			rockInterval = randSpawnInterval(mt);
			rockTime = 0;
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