#include "GameEngine.h"



namespace ASSB
{
	template<typename T>
	ComponentHandle<T> GameEngine::GetComponent(Globals::ObjectID id)
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

	// Sound Emitter
	template<>
	inline ComponentHandle<SoundEmitterComponent> GameEngine::GetComponent(Globals::ObjectID id)
	{
		return ComponentHandle<SoundEmitterComponent>(id, SoundEmitters);
	}

	template<>
	inline ComponentHandle<RigidBodyComponent> GameEngine::GetComponent(Globals::ObjectID id)
	{
		return ComponentHandle<RigidBodyComponent>(id, RigidBodies);
	}
}
