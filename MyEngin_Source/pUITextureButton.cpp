#include "pUITextureButton.h"
#include "pInput.h"
#include <string>
#include <cwchar>
namespace p
{
	UITextureButton::UITextureButton()
	{
	}
	UITextureButton::~UITextureButton()
	{
	}
	void UITextureButton::OnInit()
	{

	}
	void UITextureButton::OnActive()
	{
	}
	void UITextureButton::OnInActive()
	{
	}
	void UITextureButton::OnUpdate()
	{
		Vector2 mousePos = Input::GetMousePosition();

		if (mPosition.x <= mousePos.x && mousePos.x <= mPosition.x + mSize.x*mTexture->GetWidth()
			&& mPosition.y <= mousePos.y && mousePos.y <= mPosition.y + mSize.y*mTexture->GetHeight())
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
	void UITextureButton::OnLateUpdate()
	{
	}
	void UITextureButton::OnRender(HDC hdc)
	{
		
		if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Bmp)
		{

			if (mTexture->IsAlpha()) { // ���İ��� ������ ���ĺ���
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
			// ����ȭ ��ų �ȼ��� �� ����
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
	void UITextureButton::OnClear()
	{

	}
}