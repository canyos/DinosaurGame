#pragma once
#include "pResources.h"
#include "pTexture.h"

namespace p {
	void LoadResources() {
		//Resources::Load<graphics::Texture>(L"Map", L"..\\.\\Resources\\img\\map\\map_pure.png");
		//Resources::Load<graphics::Texture>(L"PACMAN", L"..\\.\\Resources\\img\\pacman\\1.png");
		//Resources::Load<graphics::Texture>(L"Effect", L"..\\.\\Resources\\effect2.png");
		//Resources::Load<graphics::Texture>(L"ocean", L"..\\.\\Resources\\CloudOcean.png");
		//Resources::Load<graphics::Texture>(L"cat", L"..\\.\\Resources\\ChickenAlpha.bmp");
		//Resources::Load<graphics::Texture>(L"player", L"..\\.\\Resources\\Player.bmp");
		
		//Resources::Load<graphics::Texture>(L"HPBAR", L"..\\.\\Resources\\HPBAR.bmp");
		//Resources::Load<graphics::Texture>(L"PixelMap", L"..\\.\\Resources\\pixelMap.bmp");

		Resources::Load<graphics::Texture>(L"SpringFloor", L"..\\Resources\\SpringFloor.bmp");
		Resources::Load<graphics::Texture>(L"Sky", L"..\\Resources\\dinosaur\\Sky.png");
		Resources::Load<graphics::Texture>(L"Ground", L"..\\Resources\\dinosaur\\Ground.png");
		Resources::Load<graphics::Texture>(L"Player", L"..\\Resources\\dinosaur\\Player.png");
		Resources::Load<graphics::Texture>(L"Cactus A", L"..\\Resources\\dinosaur\\Cactus A.png");
		Resources::Load<graphics::Texture>(L"Cactus B", L"..\\Resources\\dinosaur\\Cactus B.png");
		Resources::Load<graphics::Texture>(L"Cactus C", L"..\\Resources\\dinosaur\\Cactus C.png");
		Resources::Load<graphics::Texture>(L"Rock A", L"..\\Resources\\dinosaur\\Back A.png");
		Resources::Load<graphics::Texture>(L"Rock B", L"..\\Resources\\dinosaur\\Back B.png");
		Resources::Load<graphics::Texture>(L"Cloud A", L"..\\Resources\\dinosaur\\Cloud A.png");
		Resources::Load<graphics::Texture>(L"Cloud B", L"..\\Resources\\dinosaur\\Cloud B.png");
		Resources::Load<graphics::Texture>(L"BtnDown", L"..\\Resources\\dinosaur\\UI Btn Down.png");
		Resources::Load<graphics::Texture>(L"BtnUp", L"..\\Resources\\dinosaur\\UI Btn On.png");
		Resources::Load<graphics::Texture>(L"GameOver", L"..\\Resources\\dinosaur\\UI Over.png");

	}
}
