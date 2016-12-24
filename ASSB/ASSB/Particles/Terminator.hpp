#pragma once

#include "Events/UpdateEvent.hpp"
#include "EventSystem/ObjectEventManager.hpp"
#include "Globals.hpp"
#include "GameEngine/ComponentHandle.h"
#include "Components/ParticleComponent.hpp"

namespace ASSB
{
	class Terminator : public EventSystem::ObjectEventManager
	{
	public:
		Globals::ObjectID Owner;
		ComponentHandle<ParticleComponent> Comp;

		Terminator(Globals::ObjectID owner);

		virtual int Update(UpdateEvent* e, ParticleBuffer::Particle& particle) = 0;

		Terminator& operator=(const Terminator& rhs);
	};
}

