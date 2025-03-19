#pragma once
#include <cstdint>
#include "pGameObject.h"
using namespace p;

class LinkingContext
{
public:

	LinkingContext();

	uint32_t GetNetworkId(GameObject* inGameObject, bool inShouldCreateIfNotFound);

	GameObject* GetGameObject(uint32_t inNetworkId) const;

	void AddGameObject(GameObject* inGameObject, uint32_t inNetworkId);

	void RemoveGameObject(GameObject *inGameObject);

private:
	std::unordered_map< uint32_t, GameObject* > mNetworkIdToGameObjectMap;
	std::unordered_map< const GameObject*, uint32_t > mGameObjectToNetworkIdMap;

	uint32_t mNextNetworkId;
};
