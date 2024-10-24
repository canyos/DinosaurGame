// Editor_Window.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Editor_Window.h"

#include "..\\MyEngin_Source\\pApplication.h"
#include "../MyEngine_Window/pLoadScene.h"
#include "../MyEngine_Window/LoadResources.h"
#include "time.h"
#include "pResources.h"
#include "pTexture.h"
#include "../MyEngine_Window/pToolScene.h"
#include "pSceneManager.h"

p::Application application;

ULONG_PTR gpToken;
Gdiplus::GdiplusStartupInput gpsi;

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
//wchar 2byte char
// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance, const wchar_t* name, WNDPROC proc);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,//프로그램의 인스턴스 핸들 (핸들을 통해서만 윈도우 메모리에 접근)
                     _In_opt_ HINSTANCE hPrevInstance, //바로앞에 실행된 현재 프로그램의 인스턴스 핸들, 없을경우에는 NULL (현재는 사용안함)
                     _In_ LPWSTR    lpCmdLine, //명령행으로 입력된 프로그램 인수(거의 쓸일 없음 argc,argv)
                     _In_ int       nCmdShow)//프로그램이 실행될 형태, 모양 정보 등이 전달됨
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(memAddr);
    // TODO: 여기에 코드를 입력합니다.
	
    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_EDITORWINDOW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance, szWindowClass, WndProc);
	MyRegisterClass(hInstance, L"TILEWINDOW", WndTileProc);//인스턴스 정보를 설정함

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EDITORWINDOW));

    MSG msg;
	//GetMessage(&msg, nullptr, 0, 0)
	// 프로세스에서 발생한 메세지를 메세지 큐에서 가져오는 함수
	// 아무것도 없으면 아무 메시지도 가져오지 않음
	
	//PeekMessage : 메세지큐에 메시지 유무에 없이 함수 리턴
	//              리턴값이 true -> 메세지있음, false ->메세지 없음
	
	while (true) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {//메세지 읽고 지워줘야함
			if (msg.message == WM_QUIT)
				break;
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {
			//메세지가 없을 경우 여기서 처리
			//게임 로직
			application.Run();
		}
	}


    // 기본 메시지 루프입니다:
    //while (GetMessage(&msg, nullptr, 0, 0)) //프로그램이 종료되지않게 함, 메시지 큐를 확인해 메시지 확인함
    //{
    //    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    //    {
    //        TranslateMessage(&msg);
    //        DispatchMessage(&msg);
    //    }
    //}
	Gdiplus::GdiplusShutdown(gpToken);
	application.Release();
    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance, const wchar_t* name, WNDPROC proc)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= proc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EDITORWINDOW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_EDITORWINDOW);
    wcex.lpszClassName  = name; //인스턴스 이름 설정
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
   const UINT width = 1600, height = 900;
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, //window창을 만들어줌, szWindowClass로 register한 정보 들고와서 설정,                                                                       
      CW_USEDEFAULT, 0, width, height, nullptr, nullptr, hInstance, nullptr); //szTitle이 이름, WS_OVERLAPPEDWINDO는 타입
																			//시작할때 위치xy, 가로세로크기 설정가능
   

   application.Initialize(hWnd, width, height);

   if (!hWnd) //윈도우에 접근 가능한 핸들 반환
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   //ShowWindow(ToolHWnd, nCmdShow);
   

   Gdiplus::GdiplusStartup(&gpToken, &gpsi, NULL);
   srand(time(NULL));
   p::LoadResources();
   p::LoadScenes();
   
   p::Scene* activeScene = p::SceneManager::GetActiveScene();
   std::wstring name = activeScene->GetName();
   if (name == L"ToolScene") {
	   HWND ToolHWnd = CreateWindowW(L"TILEWINDOW", L"TileWindow", WS_OVERLAPPEDWINDOW,
		   0, 0, width, height, nullptr, nullptr, hInstance, nullptr);
	   //Tile윈도우 크기 조정 -- tool
	   p::graphics::Texture* texture =
		   p::Resources::Find<p::graphics::Texture>(L"SpringFloor");

	   RECT rect = { 0,0, texture->GetWidth(), texture->GetHeight() };
	   AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);//윈도우 설정해줌

	   UINT toolWidth = rect.right - rect.left,
		   toolHeight = rect.bottom - rect.top;

	   SetWindowPos(ToolHWnd, nullptr, width, 0, toolWidth, toolHeight, 0);//윈도우 위치, 크기 설정
	   ShowWindow(ToolHWnd, true);
	   UpdateWindow(ToolHWnd);
   }
   
   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}




// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
