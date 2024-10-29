#pragma once
#include "CommonInclude.h"
#include "pUIBase.h"
namespace p {
	using namespace enums;
	class UIManager
	{
	public:
		static void Initialize();
		static void OnLoad(std::wstring name);
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);
		static void OnComplete(UIBase* addUI);
		static void OnFail();
		static void Release();

		static void Push(std::wstring name);
		static void Pop(std::wstring name);

	private:
		static std::unordered_map<std::wstring, UIBase*> mUIs;//UI type�� ���� UIBase��
		static std::stack<UIBase*> mUIBases; //UI�� ����������
		static std::queue<std::wstring> mRequestUiQueue; //�޼��� ť
		static UIBase* mActiveUI; 
	};
}


