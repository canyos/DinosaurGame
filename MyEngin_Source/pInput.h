#pragma once
#include "CommonInclude.h"
#include "pMath.h"
namespace p {
	enum class eKeyState {
		Down, //누름
		Pressed, //계속 누름
		Up, //누르다가 뗌
		None //아무것도안함
	};
	enum class eKeyCode {
		Q,W,E,R,T,Y,U,I,O,P,
		A,S,D,F,G,H,J,K,L,
		Z,X,C,V,B,N,M, 
		Left,Right,Down,Up,
		LButton, MButton, RButton,
		END,
	};
	class Input
	{
	public:
		struct Key {
			eKeyCode keyCode; //무슨 키인지
			eKeyState state; //상태
			bool bPressed; // 눌렸는지
		};
		static void Initialize();
		
		static void Update();

		__forceinline static bool GetKeyDown(eKeyCode code) { return Keys[(UINT)code].state == eKeyState::Down; }
		__forceinline static bool GetKeyUp(eKeyCode code) { return Keys[(UINT)code].state == eKeyState::Up; }
		__forceinline static bool GetKey(eKeyCode code) { return Keys[(UINT)code].state == eKeyState::Pressed; }
		__forceinline static math::Vector2 GetMousePosition() { return mMousePosition; }
	private:
		//eKeyState mState[] = eKeyState::Up;
		static std::vector<Key> Keys; //모든 키를 관리하는 vector, input전체가 공유가능하게 static으로 선언
		static math::Vector2 mMousePosition;
	private:
		static void createKeys();
		static void updateKeys();
		static void updateKeyDown(Input::Key & key);
		static void updateKeyUp(Input::Key & key);
		static void updateKey(Input::Key& key);
		static bool isKeyDown(eKeyCode code);
		static void clearKeys();
		static void getMousePositionByWindow();
	};
}


