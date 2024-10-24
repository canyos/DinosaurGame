#include "pApplication.h"
#include "pInput.h"
#include "pTime.h"
#include "pSceneManager.h"
#include "pResources.h"
#include "pCollisionManager.h"
#include "pUIManager.h"
#include "pFmod.h"

namespace p {
	Application::Application() :mHwnd(nullptr), mHdc(nullptr), mHeight(0), mWidth(0), mBackHdc(NULL), mBackBitmap(NULL)
	{
	}
	Application::~Application()
	{
	}
	void Application::Initialize(HWND hwnd,UINT width, UINT height)
	{
		adjustWindowRect(hwnd, width, height);
		createBuffer(width, height);
		InitializeEtc();

		Fmod::Initialize();
		CollisionManager::Initialize();
		UIManager::Initialize();
		SceneManager::Initialize();
		
	}
	void Application::InitializeEtc()
	{
		Input::Initialize();
		Time::Initialize();
	}
	void Application::clearRenderTarget() {
		HBRUSH grayBrush = (HBRUSH)CreateSolidBrush(RGB(128,128,128));
		HBRUSH oldBrush = (HBRUSH)SelectObject(mBackHdc, grayBrush);

		Rectangle(mBackHdc, -1, -1, 1601, 901);
		(HBRUSH)SelectObject(mBackHdc, oldBrush);
		DeleteObject(grayBrush);
	}

	void Application::copyRenderTarget(HDC source, HDC dest)
	{
		BitBlt(dest, 0, 0, mWidth, mHeight, source, 0, 0, SRCCOPY);
	}

	void Application::adjustWindowRect(const HWND &hwnd, const UINT &width, const UINT &height)
	{
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);

		RECT rect = { 0,0, width, height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);//윈도우 설정해줌

		mWidth = rect.right - rect.left, mHeight = rect.bottom - rect.top;

		SetWindowPos(mHwnd, nullptr, 0, 0, mWidth, mHeight, 0);//윈도우 위치, 크기 설정
		ShowWindow(mHwnd, true);
	}

	void Application::createBuffer(const UINT &width, const UINT &height)
	{
		//윈도우 해상도에 맞는 백버퍼(도화지) 생성
		mBackBitmap = CreateCompatibleBitmap(mHdc, width, height);

		//백버퍼를 가르킬 dc생성
		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBitmap);
		DeleteObject(oldBitmap);
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();

		Destroy();
	}

	void Application::Update()
	{
		//키보드입력받음
		//오른쪽 x+ 왼쪽 x-
		Input::Update();
		
		
		Time::Update();
		CollisionManager::Update();
		UIManager::Update();
		SceneManager::Update();
	}

	void Application::LateUpdate()
	{
		CollisionManager::LateUpdate();
		UIManager::LateUpdate();
		SceneManager::LateUpdate();
	}

	void Application::Render() //처음만 그리는게 아니라 매번 새로 그림
	{
		//Rectangle(mHdc, 0, 0, 1600, 900);//매번 배경 새로 그려 잔상 지움-> 깜빡거림(flickering) 문제
		//window의 크기가 1600,900 이므로 실제 그릴 수 있는 영역은 더 작음
		//더블 버퍼링으로 해결
		//dc를 두개 그려 번갈아가면서 화면에 출력

		clearRenderTarget();

		
		Time::Render(mBackHdc);
		CollisionManager::Render(mBackHdc);
		UIManager::Render(mBackHdc);
		SceneManager::Render(mBackHdc);

		//backbuffer를 원본 버퍼로 복사
		copyRenderTarget(mBackHdc, mHdc);
	}
	void Application::Destroy()
	{
		SceneManager::Destroy();
	}
	void Application::Release() {
		SceneManager::Release();
		UIManager::Release();
		Resources::Release();
	}
}

