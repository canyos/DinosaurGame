#pragma once
#include "pResource.h"
#include "pTexture.h"
namespace p {
	class Animation : public Resource
	{
	public:
		struct Sprite {
			Vector2 leftTop; // 이미지 시작 위치
			Vector2 size; //이미지 한개의 크기
			Vector2 offset; //중앙을 어디로 설정할 것인지
			float duration;
			Sprite()
				:leftTop(Vector2::Zero),
				size(Vector2::Zero),
				offset(Vector2::Zero),
				duration(0.0f)
			{

			}
		};
		Animation();
		~Animation();
		HRESULT Load(const std::wstring& path) override;
		void CreateAnimation(const std::wstring& name,
			graphics::Texture* spriteSheet, //이미지 텍스쳐
			Vector2 leftTop, // 이미지 시작 위치
			Vector2 size, //이미지 한개의 크기
			Vector2 offset, //중앙을 어디로 설정할 것인지
			UINT spriteLength, // 연속으로 보여줄 이미지 개수
			float duration); //한장당 지속시간

		void Update();
		void Render(HDC hdc);
		void Reset();

		bool IsComplete() {	return mbComplete;	}
		void SetAnimator(class Animator* animator) { mAnimator = animator; }

	private:
		class Animator* mAnimator;
		graphics::Texture* mTexture;
		std::vector<Sprite> mAnimationSheet;
		int mIndex;// 몇번인덱스 보여줄지 
		float mTime; //몇초단위로 넘길건지
		bool mbComplete; //다시 돌아갈지 체크
	};
}


