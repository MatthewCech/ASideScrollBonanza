#include "Updater.hpp"
#include "Globals.hpp"
#include "GameEngine/GameEngine.h"

namespace ASSB
{
	Updater::Updater(Globals::ObjectID owner)
		: EventSystem::ObjectEventManager(Globals::EventSystemInstance)
		, Owner(owner)
		, Comp(GameEngine::Instance->GetComponent<ParticleComponent>(owner))
	{
		
	}

	Updater::~Updater()
	{
	}

	Updater & Updater::operator=(const Updater & rhs)
	{
		Owner = rhs.Owner;
		Comp = rhs.Comp;
		return *this;
	}
}

