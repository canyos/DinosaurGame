#include "pUIHUD.h"
#include "pResources.h"

namespace p
{
	UIHUD::UIHUD()
	{
	}
	UIHUD::~UIHUD()
	{
	}
	void UIHUD::OnInit()
	{
		
	}
	void UIHUD::OnActive()
	{
		//int* p = new int;
	}
	void UIHUD::OnInActive()
	{
	}
	void UIHUD::OnUpdate()
	{
	}
	void UIHUD::OnLateUpdate()
	{
	}
	void UIHUD::OnRender(HDC hdc)
	{
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
	void UIHUD::OnClear()
	{
		//delete p;
	}
}