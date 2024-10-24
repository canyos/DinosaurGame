#include "Time.h"
#include "pTime.h"
namespace p {
	LARGE_INTEGER Time::CpuFrequency = {};
	LARGE_INTEGER Time::PrevFrequency = {};
	LARGE_INTEGER Time::CurrentFrequency = {};
	float Time::DeltaTimeValue = 0.0f;
	void Time::Initialize()
	{
		//cpu의 고유진동수
		QueryPerformanceFrequency(&CpuFrequency);
		//프로그램이 시작 했을 때 현재 진동 수
		QueryPerformanceCounter(&PrevFrequency);
	}
	void Time::Update()
	{
		// Update되었는지/진동수 -> deltaTime
		QueryPerformanceCounter(&CurrentFrequency);
		float differenceFrequency = static_cast<float> (CurrentFrequency.QuadPart - PrevFrequency.QuadPart);

		//차이를 cpu고유진동수로 나누어 시간 구함
		DeltaTimeValue = differenceFrequency / static_cast<float> (CpuFrequency.QuadPart);

		//현재 진동수를 과거 진동수로 업데이트
		PrevFrequency.QuadPart = CurrentFrequency.QuadPart;
	}
	void Time::Render(HDC hdc)
	{
		static float time = 0.0f;
		time += DeltaTimeValue;
		float fps = 1.0f / DeltaTimeValue;

		wchar_t str[50] = L"";
		swprintf_s(str, 50, L"Time : %d", (int)fps);
		int len = wcsnlen_s(str, 50);

		

		TextOutW(hdc, 0, 0, str, len);
	}
}