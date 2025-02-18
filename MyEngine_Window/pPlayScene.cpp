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
#include "pBackgroundScript.h"
#include "pColliderComponent.h"
#include "pUITextButton.h"
#include "pConnectionManager.h"
#include <cwchar> // swprintf 사용을 위해 필요


namespace p
{
	PlayScene::PlayScene()
	{
		hFont = CreateFont(
			24,                // 글꼴 크기 (높이)
			0,                 // 너비 (0이면 자동 비율 유지)
			0, 0,              // 각도
			FW_BOLD,           // 굵기
			FALSE, FALSE, FALSE, // 기울임, 밑줄, 취소선
			DEFAULT_CHARSET,   // 문자 집합
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_SWISS,
			L"Arial");         // 글꼴 이름

		PlayScene::map = {0};

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

		isEnd = false;
		mTime = 0.0f;
		score = 0;
		HighScore = ConnectionManager::GetHighScore();

		//main camera
		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(344.0f, 442.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		renderer::mainCamera = cameraComp;
		//camera->AddComponent<PlayerScript>();


		mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);
		//object::DontDestroyOnLoad(mPlayer);
		//mPlayer->AddComponent<AudioListener>();

		PlayerScript* plScript = mPlayer->AddComponent<PlayerScript>();
		mPlayer->AddComponent<ColliderComponent>();
		BoxCollider2D* collider = new BoxCollider2D();
		collider->SetOriginalSize(Vector2(90.0f, 60.0f));
		collider->SetOffset(Vector2(0.0f, 0.0f));
		mPlayer->AddCollider(collider);

		BoxCollider2D* collider2 = new BoxCollider2D();
		collider2->SetOriginalSize(Vector2(70.0f, 80.0f));
		collider2->SetOffset(Vector2(0.0f, 0.0f));
		mPlayer->AddCollider(collider2);

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
		floor->AddComponent<ColliderComponent>();
		BoxCollider2D* floorCol = new BoxCollider2D();
		floorCol->SetOriginalSize(Vector2(1600.0f, 200.0f));
		floor->AddComponent<FloorScript>();
		floor->AddCollider(floorCol);

		BackGround* bg1 = object::Instantiate<BackGround>(eLayerType::BackGround, Vector2(0.0f, 0.0f));
		bg1->SetName(L"Sky");
		SpriteRenderer* bgSr1 = bg1->AddComponent<SpriteRenderer>();
		graphics::Texture* skyTexture = Resources::Find<graphics::Texture>(L"Sky");
		bgSr1->SetTexture(skyTexture);
		bgSr1->SetSize(Vector2(34.0f,11.0f));

		for (int i = 0; i < 3; i++) {
			BackGround* bg2 = object::Instantiate<BackGround>(eLayerType::BackGround, Vector2(0.0f+800.0f*i, 700.0f));
			bg2->SetName(L"ground");
			bg2->AddComponent<BackgroundScript>();
			SpriteRenderer* bgSr2 = bg2->AddComponent<SpriteRenderer>();
			graphics::Texture* groundTexture = Resources::Find<graphics::Texture>(L"Ground");
			bgSr2->SetTexture(groundTexture);
			bgSr2->SetSize(Vector2(17.0f, 4.2f));
		}
		
		FILE* pFile = fopen("../Tile", "r+");
		if (pFile != NULL) {
			for (;;)
			{
				int height = 0;
				if (fread(&height, sizeof(int), 1, pFile) != 1)
					break;

				map.push_back(height);
			}
			fclose(pFile);
		}


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
			cactus->AddComponent<ColliderComponent>();
			graphics::Texture* cactusATexture = Resources::Find<graphics::Texture>(cactusName[randNum]);
			BoxCollider2D* cactusCollider = new BoxCollider2D();

			SpriteRenderer* cactusSr = cactus->AddComponent<SpriteRenderer>();
			cactusSr->SetTexture(cactusATexture);
			Transform* cacTr = cactus->AddComponent<Transform>();
			cactus->AddComponent<CactusScript>();
			
			int sz = map.size();
			int h = map[(int)mTime%sz];
			mTime += 1;
			if (randNum == 0) {
				cactusATexture->SetWidth(12);
				cactusATexture->SetHeight(20);
				cacTr->SetPosition(Vector2(1600.0f, 700.0f - 20.0f*h));
				cacTr->SetScale(Vector2(3.0f, 1.0f*h));
				cactusCollider->SetOriginalSize(Vector2(36.0f, 20.0f*h));
				cactusCollider->SetOffset(Vector2::Zero);
			}
			else if (randNum == 1) {
				cactusATexture->SetWidth(21);
				cactusATexture->SetHeight(15);
				cacTr->SetPosition(Vector2(1600.0f, 700.0f - 15.0f*h));
				cacTr->SetScale(Vector2(3.0f, 1.0f*h));
				cactusCollider->SetOriginalSize(Vector2(63.0f, 15.0f*h));
				cactusCollider->SetOffset(Vector2::Zero);
			}
			else {
				cactusATexture->SetWidth(28);
				cactusATexture->SetHeight(20);
				cacTr->SetPosition(Vector2(1600.0f, 700.0f - 20.0f*h));
				cacTr->SetScale(Vector2(3.0f, 1.0f*h));
				cactusCollider->SetOriginalSize(Vector2(84.0f, 20.0f*h));
				cactusCollider->SetOffset(Vector2::Zero);
			}
			cactus->AddCollider(cactusCollider);

			std::uniform_int_distribution<int> randSpawnInterval(5, 10);
			spawnInterval = randSpawnInterval(mt);
			spawnTime = 0;
		}
		
		if (cloudTime % cloudInterval == 0) {
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_int_distribution<int> cloudRand(0, 500);
			auto randNum = cloudRand(mt);

			Particle* cloud = object::Instantiate<Particle>(enums::eLayerType::Particle);
			cloud->SetSpeed(200.0f);
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

			std::uniform_int_distribution<int> randSpawnInterval(100, 200);
			cloudInterval = randSpawnInterval(mt);
			cloudTime = 0;
		}

		if (rockTime % rockInterval == 0) {
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_int_distribution<int> rockRand(700, 800);
			auto randNum = rockRand(mt);

			Particle* rock = object::Instantiate<Particle>(enums::eLayerType::Particle);
			rock->SetSpeed(340.0f);
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

			std::uniform_int_distribution<int> randSpawnInterval(100, 300);
			rockInterval = randSpawnInterval(mt);
			rockTime = 0;
		}
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
		
		if (prevEnd == false && isEnd == true) {
			UIManager::Push(L"GameOver");
			UIManager::Push(L"Restart");

			score = mTime;
			UITextButton* saveScore = (UITextButton*)UIManager::findUI(L"Save Score");
			if (saveScore == nullptr)
				assert(false);

			saveScore->SetClickEvent([=]() {
				ConnectionManager::SaveScore(score);
				this->Reset();
			});
			UIManager::Push(L"Save Score");

			UITextButton* currentScore = (UITextButton*)UIManager::findUI(L"current Score");
			if (currentScore == nullptr)
				assert(false);
			currentScore->SetText(L"score : " + std::to_wstring(score));
			UIManager::Push(L"current Score");

			UITextButton* highScore = (UITextButton*)UIManager::findUI(L"high Score");
			if (highScore == nullptr)
				assert(false);
			highScore->SetText(L"high score : " + std::to_wstring(HighScore));
			UIManager::Push(L"high Score");

		}
		else if (prevEnd == true && isEnd == false){
			UIManager::Pop(L"GameOver");
			UIManager::Pop(L"Restart");
			UIManager::Pop(L"Save Score");
			UIManager::Pop(L"current Score");
			UIManager::Pop(L"high Score");
		}
		prevEnd = isEnd;
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		if (isEnd) {
			wchar_t str[50] = L"";
			SetBkMode(hdc, TRANSPARENT);
			HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

			int len = wcsnlen_s(str, 50);
			swprintf_s(str, 50, L"score : %d ", score);
			TextOutW(hdc, 780, 500, str, len);
			swprintf_s(str, 50, L"score : %d ", HighScore);
			TextOutW(hdc, 880, 500, str, len);

			SelectObject(hdc, hOldFont);
			SetBkMode(hdc, OPAQUE);
		}

	}
	void PlayScene::OnEnter()
	{
		Scene::OnEnter();

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Animal, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
		isEnd = false;

	}
	void PlayScene::OnExit()
	{
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Animal, false);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Floor, false);
		Scene::OnExit();
	}
}