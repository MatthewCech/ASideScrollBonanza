#include "GameEngine.h"



namespace ASSB
{
	template<typename T>
	ComponentHandle<T> GameEngine::GetComponent(Globals::ObjectID id)
	{
		throw std::exception("Not Implemented");
	}

	template <typename T>
	void GameEngine::AddComponent(Globals::ObjectID id)
	{
		throw std::exception("Not Implemented");
	}

	  ////////////////////////////////////////////////////
	 // Add template specialization for each component //
	////////////////////////////////////////////////////
	// Transform
	template<>
	inline ComponentHandle<TransformComponent> GameEngine::GetComponent(Globals::ObjectID id)
	{
		return ComponentHandle<TransformComponent>(id, Transforms);
	}
	template<>
	inline void GameEngine::AddComponent<TransformComponent>(Globals::ObjectID id)
	{
		//Transforms.emplace(NextID - 1, TransformComponent());
		Transforms.emplace(id, std::unique_ptr<TransformComponent>(new TransformComponent()));
	}


	// Sound Emitter
	template<>
	inline ComponentHandle<SoundEmitterComponent> GameEngine::GetComponent(Globals::ObjectID id)
	{
		return ComponentHandle<SoundEmitterComponent>(id, SoundEmitters);
	}
	template<>
	inline void GameEngine::AddComponent<SoundEmitterComponent>(Globals::ObjectID id)
	{
		SoundEmitters.emplace(id, std::unique_ptr<SoundEmitterComponent>(new SoundEmitterComponent()));
	}


	// Rigid Body
	template<>
	inline ComponentHandle<RigidBodyComponent> GameEngine::GetComponent(Globals::ObjectID id)
	{
		return ComponentHandle<RigidBodyComponent>(id, RigidBodies);
	}
	template<>
	inline void GameEngine::AddComponent<RigidBodyComponent>(Globals::ObjectID id)
	{
		RigidBodies.emplace(id, std::unique_ptr<RigidBodyComponent>(new RigidBodyComponent()));
	}

	//Sprite
	template<>
	inline ComponentHandle<SpriteComponent> GameEngine::GetComponent(Globals::ObjectID id)
	{
		return ComponentHandle<SpriteComponent>(id, Sprites);
	}
	template<>
	inline void GameEngine::AddComponent<SpriteComponent>(Globals::ObjectID id)
	{
		Sprites.emplace(id, std::unique_ptr<SpriteComponent>(new SpriteComponent()));
	}


	// Menus
	template<>
	inline ComponentHandle<MenuComponent> GameEngine::GetComponent(Globals::ObjectID id)
	{
		return ComponentHandle<MenuComponent>(id, Menus);
	}
	template<>
	inline void GameEngine::AddComponent<MenuComponent>(Globals::ObjectID id)
	{
		Menus.emplace(id, std::unique_ptr<MenuComponent>(new MenuComponent()));
	}


	// Player Managers
	template<>
	inline ComponentHandle<PlayerManagerComponent> GameEngine::GetComponent(Globals::ObjectID id)
	{
		return ComponentHandle<PlayerManagerComponent>(id, PlayerManagers);
	}
	template<>
	inline void GameEngine::AddComponent<PlayerManagerComponent>(Globals::ObjectID id)
	{
		PlayerManagers.emplace(id, std::unique_ptr<PlayerManagerComponent>(new PlayerManagerComponent()));
	}
}
