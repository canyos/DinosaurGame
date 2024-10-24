#pragma once
#include "CommonInclude.h"
#include "pBoxCollider2D.h"
#include "pCircleCollider2D.h"

namespace p {
	using namespace enums;
	union CollisionID {
		struct {
			UINT32 left;
			UINT32 right;
		};
		UINT64 id;
	};
	class CollisionManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);
		static void Clear();

		static void CollisionLayerCheck(eLayerType left, eLayerType right, bool enable);
		static void LayerCollision(class Scene* scene, eLayerType row, eLayerType col);
		static void ColliderCollision(Collider* left, Collider* right);
		static bool Intersect(Collider* left, Collider* right);
		static bool checkCollideCircleRect(Collider* circle, Collider* rect);
	private:
		static std::bitset <(UINT)eLayerType::Max> mCollisionLayerMatrix[(UINT)eLayerType::Max];
		static std::unordered_map<UINT64, bool> mCollisionMap;
	};
}


