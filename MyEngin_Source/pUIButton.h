#pragma once
#include "pUIBase.h"
#include "pTexture.h"
#include <functional>

namespace p {
	class UIButton : public UIBase
	{
	public:
		UIButton();
		~UIButton();

		void SetClickEvent(std::function<void()> func) { mOnClick = func; }

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnUpdate() override;
		virtual void OnLateUpdate() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

	private:
		Event mOnClick;
	};
}



