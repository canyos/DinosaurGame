#include "pUIManager.h"
#include "pUIHUD.h"
#include "pUIButton.h"
#include "pSceneManager.h"
#include <string>
#include "pResources.h"
#include "pScene.h"
#include "pUITextButton.h"
#include "pUITextureButton.h"
namespace p {
	std::unordered_map<std::wstring, UIBase*> UIManager::mUIs = {};
	std::stack<UIBase*> UIManager::mUIBases = {};
	std::queue<std::wstring> UIManager::mRequestUiQueue = {};
	UIBase* UIManager::mActiveUI = nullptr;
	void UIManager::Initialize()
	{
		UITextButton* startButton = new UITextButton();
		startButton->SetUIName(L"Start Button");
		startButton->SetPos(Vector2(100.0f, 100.0f));
		startButton->SetSize(Vector2(200.0f, 50.0f));
		startButton->SetClickEvent([]() {
			SceneManager::LoadScene(L"PlayScene");
		});
		mUIs.insert(std::make_pair(L"Start Button", startButton));

		UITextButton* exitButton = new UITextButton();
		exitButton->SetUIName(L"Exit Button");
		exitButton->SetPos(Vector2(100.0f, 400.0f));
		exitButton->SetSize(Vector2(200.0f, 50.0f));
		exitButton->SetClickEvent([]() {
			PostQuitMessage(0);
		});
		mUIs.insert(std::make_pair(L"Exit Button", exitButton));

		UIHUD* gameOver = new UIHUD();
		graphics::Texture* gameOverTexture = Resources::Find<graphics::Texture>(L"GameOver");
		gameOverTexture->SetWidth(270.0f);
		gameOverTexture->SetHeight(42.0f);
		
		gameOver->SetTexture(gameOverTexture);
		gameOver->SetUIName(L"GameOver");
		gameOver->SetName(L"GameOver");
		gameOver->SetPos(Vector2(665.0f, 408.0f));
		gameOver->SetSize(Vector2(6.0f, 6.0f));
		mUIs.insert(std::make_pair(L"GameOver", gameOver));

		UITextureButton* restart = new UITextureButton();
		graphics::Texture* restartTexture = Resources::Find<graphics::Texture>(L"BtnUp");
		restart->SetUIName(L"Restart");
		restart->SetTexture(restartTexture);

		restart->SetPos(Vector2(650.0f, 500.0f));
		restart->SetSize(Vector2(6.0f, 6.0f));
		restart->SetClickEvent([]() {
			Scene* activeScene = SceneManager::GetActiveScene();
			activeScene->Reset();
		});
		mUIs.insert(std::make_pair(L"Restart", restart));

		UITextButton* saveScore = new UITextButton();
		saveScore->SetUIName(L"Save Score");
		saveScore->SetPos(Vector2(900.0f, 500.0f));
		saveScore->SetSize(Vector2(100.0f, 100.0f));
		mUIs.insert(std::make_pair(L"Save Score", saveScore));

	}
	void UIManager::OnLoad(std::wstring uiName)
	{
		std::unordered_map<std::wstring, UIBase*>::iterator iter = mUIs.find(uiName);
		if (iter == mUIs.end()) {//�ε� ����
			OnFail();
			return;
		}

		OnComplete(iter->second);//�ε� ����

	}
	void UIManager::Update()
	{
		std::stack<UIBase*> uiBases = mUIBases;
		
		while (!uiBases.empty()) { //���� ���� UI������Ʈ�ϱ�
			UIBase* uiBase = uiBases.top();
			uiBase->Update();
			uiBases.pop();
		}

		

		if (mRequestUiQueue.size() > 0) { //��������Ұ������� �ε��ϱ�
			std::wstring requestUIName = mRequestUiQueue.front();
			mRequestUiQueue.pop();
			OnLoad(requestUIName);
		}
	}
	void UIManager::LateUpdate()
	{
		std::stack<UIBase*> uiBases = mUIBases;
		while (!uiBases.empty()) { //���� ���� UI������Ʈ�ϱ�
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

		while (!uiBases.empty()) { //���� ���� UI������Ʈ�ϱ�
			UIBase* uiBase = uiBases.top();
			if (uiBase) {
				//uiBase->Render(hdc);
				tempStack.push(uiBase);
				uiBases.pop();
			}
		}
		while (!tempStack.empty()) { //���� ���� UI������Ʈ�ϱ�
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

		//���� ��üȭ�� UI�� �߰��ɰŶ��
		//������ ���� ��Ȱ��ȭ

		if (addUI->IsFullScreen()) {
			std::stack<UIBase*> uiBases = mUIBases;
			while (!uiBases.empty()) { 
				UIBase* uiBase = uiBases.top();
				uiBases.pop();
				if (uiBase) {
					uiBase->InActive();//��Ȱ��ȭ
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
	void UIManager::Push(std::wstring UIName)
	{
		mRequestUiQueue.push(UIName);
	}
	void UIManager::Pop(std::wstring name)
	{
		if (mUIBases.size() <= 0)
			return;

		//�ش� ui �Ѱ��� ���ÿ��� ������
		std::stack<UIBase*> tempStack;
		UIBase* uiBase = nullptr;

		while (mUIBases.size() > 0) {
			uiBase = mUIBases.top();
			mUIBases.pop();

			if (uiBase->GetUIName().compare( name))//�ٸ��� ������ ����
			{
				tempStack.push(uiBase);
				continue;
			}

			if (uiBase->IsFullScreen()) //��üȭ���̸� �ؿ��� ���� Ȱ��ȭ
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

		while (tempStack.size() > 0)//temp�ٽ� ���� �־���
		{
			uiBase = tempStack.top();
			tempStack.pop();
			mUIBases.push(uiBase);
		}

		if (mUIBases.empty())
			mActiveUI = nullptr;
		else
			mActiveUI = mUIBases.top();
	}
}
