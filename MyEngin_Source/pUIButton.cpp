#include "pUIButton.h"
#include "pInput.h"
#include <string>
#include <cwchar>
namespace p
{
	UIButton::UIButton()
	{
	}
	UIButton::~UIButton()
	{
	}
	void UIButton::OnInit()
	{

	}
	void UIButton::OnActive()
	{
	}
	void UIButton::OnInActive()
	{
	}
	void UIButton::OnUpdate()
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
	void UIButton::OnLateUpdate()
	{
	}
	void UIButton::OnRender(HDC hdc)
	{
		if (mTexture == nullptr) {
			Rectangle(hdc, mPosition.x, mPosition.y, mPosition.x + mSize.x, mPosition.x + mPosition.y);

			/*wchar_t str[50] = L"Title  Scene";
			TextOutW(hdc, 0, 0, str, lstrlenW(str));*/

			size_t length = UIName.length();

			const wchar_t* str = UIName.c_str();
			int a = 0;
			TextOutW(hdc, mPosition.x + mSize.x / 2.0f - UIName.length()*3.0f, mPosition.y + mSize.y / 2.0f + 15, str, lstrlenW(str));
		}
		else {
			if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Bmp)
			{

				if (mTexture->IsAlpha()) { // 알파값이 있으면 알파블렌드
					BLENDFUNCTION func = {};
					func.BlendOp = AC_SRC_OVER;
					func.BlendFlags = 0;
					func.AlphaFormat = AC_SRC_ALPHA;
					func.SourceConstantAlpha = 255; // 0(transparent) ~ 255(Opaque)
					AlphaBlend(hdc
						, mPosition.x
						, mPosition.y
						, mTexture->GetWidth()
						, mTexture->GetHeight()
						, mTexture->GetHdc()
						, 0, 0
						, mTexture->GetWidth(), mTexture->GetHeight()
						, func);
				}
				else {
					//https://blog.naver.com/power2845/50147965306
					TransparentBlt(hdc, mPosition.x, mPosition.y
						, mTexture->GetWidth() * mSize.x
						, mTexture->GetHeight() * mSize.y
						, mTexture->GetHdc()
						, 0, 0
						, mTexture->GetWidth(), mTexture->GetHeight()
						, RGB(255, 0, 255));
				}
			}
			else if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Png)
			{
				// 투명화 시킬 픽셀의 색 범위
				Gdiplus::ImageAttributes imgAtt = {};
				imgAtt.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));

				Gdiplus::Graphics graphcis(hdc);

				graphcis.TranslateTransform(mPosition.x, mPosition.y);
				graphcis.TranslateTransform(-mPosition.x, -mPosition.y);

				graphcis.DrawImage(mTexture->GetImage()
					, Gdiplus::Rect
					(
						mPosition.x, mPosition.y
						, mTexture->GetWidth() * mSize.x
						, mTexture->GetHeight() *mSize.y
					)
					, 0, 0
					, mTexture->GetWidth(), mTexture->GetHeight()
					, Gdiplus::UnitPixel
					, nullptr/*&imgAtt*/);
			}
		}
	}
	void UIButton::OnClear()
	{

	}
}