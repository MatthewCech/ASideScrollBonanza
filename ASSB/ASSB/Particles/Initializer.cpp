#include "Initializer.hpp"
#include "GameEngine/GameEngine.h"

ASSB::Initializer::Initializer(Globals::ObjectID owner)
	: EventSystem::ObjectEventManager(Globals::EventSystemInstance)
	, Owner(owner)
	, Comp(GameEngine::Instance->GetComponent<ParticleComponent>(owner))
{

}

ASSB::Initializer::~Initializer()
{

}

ASSB::Initializer & ASSB::Initializer::operator=(const Initializer & rhs)
{
	Owner = rhs.Owner;
	Comp = rhs.Comp;
	return *this;
}
