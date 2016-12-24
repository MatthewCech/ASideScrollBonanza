#include "Emitter.hpp"
#include "GameEngine/GameEngine.h"

ASSB::Emitter::Emitter(Globals::ObjectID owner)
	: EventSystem::ObjectEventManager(Globals::EventSystemInstance)
	, Owner(owner)
	, Comp(GameEngine::Instance->GetComponent<ParticleComponent>(owner))
{

}

ASSB::Emitter::~Emitter()
{
}

ASSB::Emitter & ASSB::Emitter::operator=(const Emitter & rhs)
{
	Owner = rhs.Owner;
	Comp = rhs.Comp;
	return *this;
}
