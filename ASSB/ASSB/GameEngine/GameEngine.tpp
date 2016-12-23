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
		Transforms.emplace(id, TransformComponent());
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
		SoundEmitters.emplace(id, SoundEmitterComponent());
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
		RigidBodies.emplace(id, RigidBodyComponent());
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
		Sprites.emplace(id, SpriteComponent());
	}


	// Menu Managers
	template<>
	inline ComponentHandle<MenuManagerComponent> GameEngine::GetComponent(Globals::ObjectID id)
	{
		return ComponentHandle<MenuManagerComponent>(id, MenuManagers);
	}
	template<>
	inline void GameEngine::AddComponent<MenuManagerComponent>(Globals::ObjectID id)
	{
		MenuManagers.emplace(id, MenuManagerComponent());
	}
}
