#include "pUITextButton.h"
#include "pInput.h"
#include <string>
#include <cwchar>
namespace p
{
	UITextButton::UITextButton()
	{
	}
	UITextButton::~UITextButton()
	{
	}
	void UITextButton::OnInit()
	{

	}
	void UITextButton::OnActive()
	{
	}
	void UITextButton::OnInActive()
	{
	}
	void UITextButton::OnUpdate()
	{
		Vector2 mousePos = Input::GetMousePosition();

		if (mPosition.x <= mousePos.x && mousePos.x <= mPosition.x + mSize.x
			&& mPosition.y <= mousePos.y && mousePos.y <= mPosition.y + mSize.y)
		{
			mbMouseOn = true;
		}
		else
		{
			mbMouseOn = false;
		}
		if (Input::GetKeyDown(eKeyCode::LButton))
		{
			if (mbMouseOn)
			{
				mOnClick();
			}
		}
	}
	void UITextButton::OnLateUpdate()
	{
	}
	void UITextButton::OnRender(HDC hdc)
	{
		Rectangle(hdc, mPosition.x, mPosition.y, mPosition.x + mSize.x, mPosition.x + mPosition.y);

		/*wchar_t str[50] = L"Title  Scene";
		TextOutW(hdc, 0, 0, str, lstrlenW(str));*/

		size_t length = UIName.length();

		const wchar_t* str = UIName.c_str();
		int a = 0;
		TextOutW(hdc, mPosition.x + mSize.x / 2.0f - UIName.length()*3.0f, mPosition.y + mSize.y / 2.0f + 15, str, lstrlenW(str));
	}
	void UITextButton::OnClear()
	{

	}
}