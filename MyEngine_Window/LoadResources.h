#pragma once
#include "pResources.h"
#include "pTexture.h"

namespace p {
	void LoadResources() {
		Resources::Load<graphics::Texture>(L"Map", L"..\\Resources\\img\\map\\map_pure.png");
		Resources::Load<graphics::Texture>(L"PACMAN", L"..\\Resources\\img\\pacman\\1.png");
		Resources::Load<graphics::Texture>(L"Effect", L"..\\Resources\\effect2.png");
		Resources::Load<graphics::Texture>(L"ocean", L"..\\Resources\\CloudOcean.png");
		Resources::Load<graphics::Texture>(L"cat", L"..\\Resources\\ChickenAlpha.bmp");
		Resources::Load<graphics::Texture>(L"player", L"..\\Resources\\Player.bmp");
		Resources::Load<graphics::Texture>(L"SpringFloor", L"..\\Resources\\SpringFloor.bmp");
		Resources::Load<graphics::Texture>(L"HPBAR", L"..\\Resources\\HPBAR.bmp");
		Resources::Load<graphics::Texture>(L"PixelMap", L"..\\Resources\\pixelMap.bmp");
	}
}
