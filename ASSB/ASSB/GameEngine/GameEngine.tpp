#include "GameEngine.h"

namespace ASSB
{
	template<typename T>
	ComponentHandle<T> GameEngine::GetComponent(Globals::ObjectID id)
	{
		throw std::exception("Not Implemented");
	}

	template<>
	inline ComponentHandle<TransformComponent> GameEngine::GetComponent(Globals::ObjectID id)
	{
		return ComponentHandle<TransformComponent>(id, Transforms);
	}
}
