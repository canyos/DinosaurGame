#pragma once
#include "pComponent.h"
#include "pAnimation.h"
#include "pTexture.h"

namespace p {
	class Animator : public Component
	{
	public:
		
		struct Event {
			void operator = (std::function<void()> func) {
				mEvent = func;
			}
			void operator()() {
				if (mEvent)
					mEvent();
			}
			std::function<void()> mEvent;
		};
		struct Events {
			Event startEvent;
			Event completeEvent;
			Event endEvent;
		};
		Animator();
		~Animator();
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void CreateAnimation(const std::wstring& name,
			graphics::Texture* spriteSheet, //이미지 텍스쳐
			Vector2 leftTop, // 이미지 시작 위치
			Vector2 size, //이미지 한개의 크기
			Vector2 offset, //중앙을 어디로 설정할 것인지
			UINT spriteLength, // 연속으로 보여줄 이미지 개수
			float duration); //한장당 지속시간
		void CreateAnimationByFolder(const std::wstring& name, 
			const std::wstring& path,
			Vector2 offset, float duration);

		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = true);
		bool IsComplete() { return mActiveAnimation->IsComplete(); }

		Events* FindEvents(const std::wstring& name);
		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);
	
	private:
		std::map<std::wstring, Animation*> mAnimations;
		Animation* mActiveAnimation;
		bool mbLoop; //루프할 것인지
		std::map<std::wstring, Events*> mEvents;
	};
}


