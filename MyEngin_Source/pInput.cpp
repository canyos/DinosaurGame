#include "pInput.h"
#include "pApplication.h"

extern p::Application application;

namespace p {
	std::vector<Input::Key> Input::Keys = {};
	math::Vector2 Input::mMousePosition = math::Vector2::One;
	int ASCII[(UINT)eKeyCode::END] = {
		'Q','W','E','R','S','T','U','I','O','P',
		'A','S','D','F','G','H','J','K','L',
		'Z','X','C','V','B','N','M',
		VK_LEFT,VK_RIGHT,VK_DOWN,VK_UP,
		VK_LBUTTON, VK_MBUTTON, VK_RBUTTON,
	};
	
	void Input::Initialize()
	{
		createKeys();
	}

	void Input::Update()
	{
		updateKeys();
	}
	void Input::createKeys() {
		for (size_t i = 0; i < (UINT)eKeyCode::END; i++) {
			Key key = {};
			key.bPressed = false;
			key.state = eKeyState::None;
			key.keyCode = (eKeyCode)i;
			Keys.push_back(key);
		}
	}
	void Input::updateKeys() {
		for (Input::Key& key : Keys)
			updateKey(key);
	}
	void Input::updateKey(Input::Key& key) {
		if (GetFocus()) {
			if (isKeyDown(key.keyCode))
				updateKeyDown(key);
			else 
				updateKeyUp(key);
			
			getMousePositionByWindow();
		}
		else {
			clearKeys();
		}
	}
	bool Input::isKeyDown(eKeyCode code) {
		return GetAsyncKeyState(ASCII[static_cast<UINT>(code)]) & 0x8000;
	}
	void Input::clearKeys()
	{
		for (Key& key : Keys) {
			if (key.state == eKeyState::Down || key.state == eKeyState::Pressed) {
				key.state = eKeyState::Up;
			}
			else if (key.state == eKeyState::Up)
				key.state = eKeyState::None;
			key.bPressed = false;
		}
	}
	void Input::getMousePositionByWindow()
	{
		POINT mousePos = {};
		GetCursorPos(&mousePos);//전체윈도우의 마우스위치 가져옴
		ScreenToClient(application.GetHwnd(), &mousePos);//내 윈도우 마우스위치가져옴
		
		mMousePosition.x = -1.0f;
		mMousePosition.y = -1.0f;

		UINT width = application.GetWidth(), height = application.GetHeight();
		if (mousePos.x < width && mousePos.x > 0) {
			mMousePosition.x = mousePos.x;
		}
		if (mousePos.y < height && mousePos.y > 0) {
			mMousePosition.y = mousePos.y;
		}

		
		
	}
	void Input::updateKeyDown(Input::Key& key) {//키가 눌렸다.
		if (key.bPressed == true)//이전 프레임에도 눌려있음
			key.state = eKeyState::Pressed;
		else//지금 누른거임
			key.state = eKeyState::Down;
		key.bPressed = true;
	}
	void Input::updateKeyUp(Input::Key& key) {//키가 안눌림
		if (key.bPressed == true)//이전 프레임에는 눌려있음
			key.state = eKeyState::Up;
		else
			key.state = eKeyState::None;
		key.bPressed = false;
	}

	
}