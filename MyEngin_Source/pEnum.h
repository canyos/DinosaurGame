#pragma once
namespace p
{
	namespace enums {
		enum class eLayerType
		{
			None,
			BackGround,
			//Tree 
			//character
			Tile,
			Floor,
			Particle,
			Animal,
			Player,
			Max = 16,
		};

		enum class eResourceType {
			Texture,
			//Mesh
			//shader
			Audioclip,
			Animation,
			Prefab,
			End,
		};
		enum class eComponentType {
			Transform,
			ColliderComponent,
			RigidBody,
			Script,
			SpriteRenderer,
			Animator,
			Camera,
			AudioListener,
			AudioSource,
			End,
		};
		enum class eColliderType
		{
			Circle2D,
			Rect2D,
			End,
		};
		enum class eUIType {
			Button,
			HpBar,
			
			End,
		};
	}
	

}