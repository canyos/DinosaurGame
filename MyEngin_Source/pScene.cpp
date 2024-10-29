#include "pScene.h"
#include "pCollisionManager.h"
#include"pTime.h"
namespace p {
	Scene::Scene() :mLayers{}, isEnd(false), prevEnd(false),mTime(0.0f)
	{
		mLayers.resize((UINT)enums::eLayerType::Max);
		for (int i = 0; i < (UINT)enums::eLayerType::Max; i++) {
			mLayers[i] = new Layer();
		}
	}
	Scene::~Scene()
	{
		for (Layer*layer : mLayers) {
			delete layer;
			layer = nullptr;
		}
	}
	void Scene::Initialize()
	{
		for (Layer* layer : mLayers) {
			if (layer == nullptr) continue;
			layer->Initialize();
		}
	}
	void Scene::Update()
	{
		mTime += Time::DeltaTime();
		for (Layer* layer : mLayers) {
			if (layer == nullptr) continue;
			layer->Update();
		}
	}
	void Scene::LateUpdate()
	{
		for (Layer* layer : mLayers) {
			if (layer == nullptr) continue;
			layer->LateUpdate();
		}
	}
	void Scene::Render(HDC hdc)
	{
		for (Layer* layer : mLayers) {
			if (layer == nullptr) continue;
			layer->Render(hdc);
		}
	}

	void Scene::Destroy()
	{
		for (Layer* layer : mLayers) {
			if (layer == nullptr) continue;
			layer->Destroy();
		}
	}

	void Scene::OnEnter() {

	}
	void Scene::OnExit() {
		CollisionManager::Clear();
	}

	void Scene::Reset()
	{
		// 기존 레이어들 정리
		for (Layer* layer : mLayers) {
			if (layer != nullptr) {
				delete layer;
			}
		}
		mLayers.clear();  // 벡터 비우기

		mLayers.resize((UINT)enums::eLayerType::Max);
		for (int i = 0; i < (UINT)enums::eLayerType::Max; i++) {
			mLayers[i] = new Layer();
		}

		// 다시 초기화
		Initialize();
	}

	void Scene::AddGameObject(GameObject * gameObject,  enums::eLayerType type)
	{
		mLayers[(UINT)type]->AddGameObject(gameObject);
	}
	void Scene::EraseGameObject(GameObject* gameObj)
	{
		eLayerType layerType = gameObj->GetLayerType();
		mLayers[(UINT)layerType]->EraseGameObjects(gameObj);

	}
}

