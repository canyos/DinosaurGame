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
		{
			//FILE* pFile = nullptr;
			//_wfopen_s(&pFile, L"../Resources/test", L"rb");
			//while (true)
			//{
			//	int idxX = 0;
			//	int idxY = 0;

			//	int posX = 0;
			//	int posY = 0;

			//	if (fread(&idxX, sizeof(int), 1, pFile) == NULL)
			//		break;
			//	if (fread(&idxY, sizeof(int), 1, pFile) == NULL)
			//		break;
			//	if (fread(&posX, sizeof(int), 1, pFile) == NULL)
			//		break;
			//	if (fread(&posY, sizeof(int), 1, pFile) == NULL)
			//		break;

			//	Tile* tile = object::Instantiate<Tile>(eLayerType::Tile, Vector2(posX, posY));
			//	TilemapRenderer* tmr = tile->AddComponent<TilemapRenderer>();
			//	tmr->SetTexture(Resources::Find<graphics::Texture>(L"SpringFloor"));
			//	tmr->SetIndex(Vector2(idxX, idxY));

			//	//mTiles.push_back(tile);
			//}
			//fclose(pFile);
		}


		//main camera
		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::None, Vector2(344.0f, 442.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		renderer::mainCamera = cameraComp;
		//camera->AddComponent<PlayerScript>();


		mPlayer = object::Instantiate<Player>(enums::eLayerType::Player);
		object::DontDestroyOnLoad(mPlayer);
		mPlayer->AddComponent<AudioListener>();

		PlayerScript* plScript = mPlayer->AddComponent<PlayerScript>();
		BoxCollider2D* collider = mPlayer->AddComponent<BoxCollider2D>();
		//CircleCollider2D* collider = mPlayer->AddComponent<CircleCollider2D>();
		collider->SetOffset(Vector2(-50.0f, -50.0f));

		graphics::Texture* playerTex = Resources::Find<graphics::Texture>(L"player");;
		Animator* playerAnimator = mPlayer->AddComponent<Animator>();
		playerAnimator->CreateAnimation(L"Idle", playerTex
			, Vector2(2000.0f, 250.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 1, 0.1f);
		playerAnimator->CreateAnimation(L"FrontGiveWater", playerTex
			, Vector2(0.0f, 2000.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 12, 0.1f);


		playerAnimator->GetCompleteEvent(L"FrontGiveWater") = std::bind(&PlayerScript::AttackEffect, plScript);


		mPlayer->GetComponent<Transform>()->SetPosition(Vector2(300.0f, 250.0f));
		mPlayer->GetComponent<Transform>()->SetRotation(0.0f);
		playerAnimator->PlayAnimation(L"Idle", false);
		mPlayer->AddComponent<RigidBody>();

		Floor* floor = object::Instantiate<Floor>(eLayerType::Floor, Vector2(0.0f, 0.0f));
		floor->SetName(L"Floor");
		SpriteRenderer* floorSr = floor->AddComponent<SpriteRenderer>();
		floorSr->SetTexture(Resources::Find<graphics::Texture>(L"PixelMap"));

		AudioSource* as = floor->AddComponent<AudioSource>();

		//BoxCollider2D* floorCol = floor->AddComponent<BoxCollider2D>();
		//floorCol->SetSize(Vector2(10.0f, 1.0f));
		//floor->AddComponent<FloorScript>();

		AudioClip* ac = Resources::Load<AudioClip>(L"BGSound", L"..\\Resources\\smw_bonus_game_end.wav");
		as->SetClip(ac);
		as->Play();

		plScript->SetPixelMapTexture(Resources::Find<graphics::Texture>(L"PixelMap"));

		///CAT
		Cat* cat = object::Instantiate<Cat>(enums::eLayerType::Animal);
		//cat->SetActive(true);
		cat->AddComponent<CatScript>();
		//cameraComp->SetTarget(cat);
		graphics::Texture* catTex = Resources::Find<graphics::Texture>(L"Cat");
		Animator* catAnimator = cat->AddComponent<Animator>(); 
		BoxCollider2D* boxCatCollider = cat->AddComponent<BoxCollider2D>();
		boxCatCollider->SetOffset(Vector2(-50.0f, -50.0f));
		//catAnimator->CreateAnimation(L"DownWalk", catTex
		//	, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//catAnimator->CreateAnimation(L"RightWalk", catTex
		//	, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//catAnimator->CreateAnimation(L"UpWalk", catTex
		//	, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//catAnimator->CreateAnimation(L"LeftWalk", catTex
		//	, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//catAnimator->CreateAnimation(L"SitDown", catTex
		//	, Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//catAnimator->CreateAnimation(L"Grooming", catTex
		//	, Vector2(0.0f, 160.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//catAnimator->CreateAnimation(L"LayDown", catTex
		//	, Vector2(0.0f, 192.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);

		//catAnimator->PlayAnimation(L"SitDown", false);
		catAnimator->CreateAnimationByFolder(L"MushroomIdle", L"..\\Resources\\Mushroom", Vector2::Zero, 0.1f);

		catAnimator->PlayAnimation(L"MushroomIdle", true);

		cat->GetComponent<Transform>()->SetPosition(Vector2(360.0f, 420.0f));
		//cat->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));



		//GameObject* sheet = object::Instantiate<GameObject>(enums::eLayerType::Particle);
		//SpriteRenderer* sheetSR = sheet->AddComponent<SpriteRenderer>();


		//graphcis::Texture* mrIdle = Resources::Find<graphcis::Texture>(L"MushroomIdle");
		//sheetSR->SetTexture(mrIdle);
		//Animator* playerAnimator = mPlayer->AddComponent<Animator>();

		// 게임 오브젝트 생성후에 레이어와 게임오브젝트들의 init함수를 호출
		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
		if (Input::GetKeyDown(eKeyCode::N)) {
			SceneManager::LoadScene(L"TitleScene");
		}
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
	
		UIManager::Push(eUIType::Button);
	}
	void PlayScene::OnExit()
	{
		UIManager::Pop(eUIType::Button);

		Scene::OnExit();
	}
}