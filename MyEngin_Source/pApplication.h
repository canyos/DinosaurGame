#pragma once
#include "CommonInclude.h"
#include "pGameObject.h"
#include "pSceneManager.h"

namespace p {
	class Application {
	public:
		Application();
		~Application();
		void Initialize(HWND hwnd, UINT width, UINT height);
		//초기화
		void Run();

		void Update();
		void LateUpdate();
		void Render();//바뀐위치로 다시 그려줌
		void Destroy();
		void Release();
		

		HDC GetHdc() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		HWND GetHwnd() { return mHwnd; }
	private:
		void clearRenderTarget();
		void copyRenderTarget(HDC source, HDC dest);
		void adjustWindowRect(const HWND &hwnd, const UINT &width, const UINT &height);
		void createBuffer(const UINT &width, const UINT &height);
		void InitializeEtc();
	private:
		HWND mHwnd;
		HDC mHdc;

		//dc가 그릴 수 있는 도화지
		//원래는 dc한개에 버퍼를 두개 만들어 왔다갔다 해야함-> 우리는 dc를 하나 더 만들것임
		HDC mBackHdc;
		HBITMAP mBackBitmap;

		UINT mWidth;
		UINT mHeight;

		//scene이 있고 scene안에 object
		std::vector<Scene*> mScenes;

	};
}