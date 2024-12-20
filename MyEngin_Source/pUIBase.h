#pragma once
#include "pEntity.h"
#include <string>
#include "pTexture.h"

namespace p {
	using namespace enums;
	class UIBase:public Entity
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}
			std::function<void()> mEvent;
		};
		UIBase();
		virtual ~UIBase();

		void Initialize(); //ui로드되면 초기화
		void Active(); //ui활성화되면 호출
		void InActive();//비활성화되면 호출

		void Update();
		void LateUpdate();
		void Render(HDC hdc);
		
		void UIClear();//UI사라질때 호출

		virtual void OnInit();
		virtual void OnActive();
		virtual void OnInActive();
		virtual void OnUpdate();
		virtual void OnLateUpdate();
		virtual void OnRender(HDC hdc);
		virtual void OnClear();

		std::wstring GetUIName() { return UIName; }
		void SetUIName(std::wstring name) { UIName = name; }
		void SetFullScrenn(bool fullscreen) { mbFulllScreen = fullscreen; }
		void SetEnabled(bool enable) { mbEnabled = enable; }
		bool IsFullScreen() { return mbFulllScreen; }
		bool IsEnabled() { return mbEnabled; }
		Vector2 GetPos() { return mPosition; }
		void SetPos(Vector2 position) { mPosition = position; }
		Vector2 GetSize() { return mSize; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetTexture(graphics::Texture* texture) { mTexture = texture; }

	protected:
		Vector2 mPosition;
		Vector2 mSize;
		bool mbMouseOn;
		std::wstring UIName;
		graphics::Texture* mTexture;

	private:
		bool mbFulllScreen;
		bool mbEnabled;
		UIBase* mParent;

	};
}


