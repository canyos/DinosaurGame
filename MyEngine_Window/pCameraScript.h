#pragma once
#include "pScript.h"
#include "pTransform.h"
namespace p {
	class CameraScript : public Script
	{
	public:
		CameraScript();
		~CameraScript();
		Vector2 mDest;
		void Initialize()override;
		void Update()override;
		void LateUpdate()override;
		void Render(HDC hdc)override;

	private:

	private:

	};
}



