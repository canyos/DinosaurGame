#pragma once
#include "pScene.h"
#include "pDontDestroyOnLoad.h"
namespace p {
	class SceneManager{
	public:
		template <typename T>
		static Scene* CreateScene(std::wstring name) {
			T* scene = new T();
			scene->SetName(name);
			mActiveScene = scene;
			scene->Initialize();
			mScene.insert({ name, scene });
			
			return scene;
		}

		static Scene* LoadScene(const std::wstring& name);

		static Scene* GetActiveScene() { return mActiveScene; }
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);

		static void Destroy();
		static void Release();

		static Scene* GetDontDestroyOnLoad() { return mDontDestroyOnLoad; }
		static std::vector<GameObject*> GetGameObjects(eLayerType layer);

	//	static SceneManager& GetInst() {
	//		static SceneManager sceneManager;
	//		return sceneManager;
	//	}
	//private:
	//	SceneManager();
	//	~SceneManager();
	// 싱글톤 패턴 하나의 객체만 만들어서 쓰겠다

	private:
		//static std::vector<Scene*> mScene;
		static std::map<const std::wstring, Scene*> mScene;
		static Scene* mActiveScene;
		static Scene* mDontDestroyOnLoad;
	};
}


