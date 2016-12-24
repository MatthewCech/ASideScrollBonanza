#include "Terminator.hpp"
#include "GameEngine/GameEngine.h"

namespace ASSB
{
	Terminator::Terminator(Globals::ObjectID owner)
		: EventSystem::ObjectEventManager(Globals::EventSystemInstance)
		, Owner(owner)
		, Comp(GameEngine::Instance->GetComponent<ParticleComponent>(owner))
	{
	}

	Terminator & Terminator::operator=(const Terminator & rhs)
	{
		Owner = rhs.Owner;
		Comp = rhs.Comp;

		return *this;
	}
}
