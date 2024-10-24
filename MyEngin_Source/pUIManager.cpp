#include "pUIManager.h"
#include "pUIHUD.h"
#include "pUIButton.h"

namespace p {
	std::unordered_map<eUIType, UIBase*> UIManager::mUIs = {};
	std::stack<UIBase*> UIManager::mUIBases = {};
	std::queue<eUIType> UIManager::mRequestUiQueue = {};
	UIBase* UIManager::mActiveUI = nullptr;
	void UIManager::Initialize()
	{
		// UI 객체 생성해주기
		UIHUD* hud = new UIHUD();
		mUIs.insert(std::make_pair(eUIType::HpBar, hud));
		UIButton* button = new UIButton();
		mUIs.insert(std::make_pair(eUIType::Button, button));
	}
	void UIManager::OnLoad(eUIType type)
	{
		std::unordered_map<eUIType, UIBase*>::iterator iter = mUIs.find(type);
		if (iter == mUIs.end()) {//로드 실패
			OnFail();
			return;
		}

		OnComplete(iter->second);//로드 성공

	}
	void UIManager::Update()
	{
		std::stack<UIBase*> uiBases = mUIBases;
		
		while (!uiBases.empty()) { //현재 켜진 UI업데이트하기
			UIBase* uiBase = uiBases.top();
			uiBase->Update();
			uiBases.pop();
		}

		

		if (mRequestUiQueue.size() > 0) { //보여줘야할거있으면 로드하기
			eUIType requestUI = mRequestUiQueue.front();
			mRequestUiQueue.pop();
			OnLoad(requestUI);
		}
	}
	void UIManager::LateUpdate()
	{
		std::stack<UIBase*> uiBases = mUIBases;
		while (!uiBases.empty()) { //현재 켜진 UI업데이트하기
			UIBase* uiBase = uiBases.top();
			if (uiBase) {
				uiBase->LateUpdate();
				uiBases.pop();
			}
		}
	}
	void UIManager::Render(HDC hdc)
	{
		std::stack<UIBase*> uiBases = mUIBases;
		std::stack<UIBase*> tempStack = {};

		while (!uiBases.empty()) { //현재 켜진 UI업데이트하기
			UIBase* uiBase = uiBases.top();
			if (uiBase) {
				//uiBase->Render(hdc);
				tempStack.push(uiBase);
				uiBases.pop();
			}
		}
		while (!tempStack.empty()) { //현재 켜진 UI업데이트하기
			UIBase* uiBase = tempStack.top();
			if (uiBase) {
				uiBase->Render(hdc);
				tempStack.pop();
			}
		}
	}
	void UIManager::OnComplete(UIBase * addUI)
	{
		if (addUI == nullptr)
			return;

		addUI->Initialize();
		addUI->Active();
		addUI->Update();

		//만약 전체화면 UI가 추가될거라면
		//나머지 전부 비활성화

		if (addUI->IsFullScreen()) {
			std::stack<UIBase*> uiBases = mUIBases;
			while (!uiBases.empty()) { 
				UIBase* uiBase = uiBases.top();
				uiBases.pop();
				if (uiBase) {
					uiBase->InActive();//비활성화
				}
			}
		}

		mUIBases.push(addUI);
		mActiveUI = addUI;
		int a = 0;
	}
	void UIManager::OnFail()
	{
		mActiveUI = nullptr;
	}
	void UIManager::Release()
	{
		for (auto iter : mUIs)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
	void UIManager::Push(eUIType type)
	{
		mRequestUiQueue.push(type);
	}
	void UIManager::Pop(eUIType type)
	{
		if (mUIBases.size() <= 0)
			return;

		//해당 ui 한개만 스택에서 뺄거임
		std::stack<UIBase*> tempStack;
		UIBase* uiBase = nullptr;

		while (mUIBases.size() > 0) {
			uiBase = mUIBases.top();
			mUIBases.pop();

			if (uiBase->GetType() != type)//다르면 템프에 넣음
			{
				tempStack.push(uiBase);
				continue;
			}

			if (uiBase->IsFullScreen()) //전체화면이면 밑에거 전부 활성화
			{
				std::stack<UIBase*> uiBases = mUIBases;
				while (!uiBases.empty())
				{
					UIBase* uiBase = uiBases.top();
					uiBases.pop();
					if (uiBase)
					{
						uiBase->Active();
						break;
					}
				}
			}

			uiBase->UIClear();
		}

		while (tempStack.size() > 0)//temp다시 전부 넣어줌
		{
			uiBase = tempStack.top();
			tempStack.pop();
			mUIBases.push(uiBase);
		}

		if (!mUIBases.empty())
			mActiveUI = nullptr;
		else
			mActiveUI = mUIBases.top();
	}
}
