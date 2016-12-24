#pragma once

#include "Events/UpdateEvent.hpp"
#include "EventSystem/ObjectEventManager.hpp"
#include "Globals.hpp"
#include "GameEngine/ComponentHandle.h"
#include "Components/ParticleComponent.hpp"

namespace ASSB
{
	class Initializer : public EventSystem::ObjectEventManager
	{
	public:
		Globals::ObjectID Owner;
		ComponentHandle<ParticleComponent> Comp;

		Initializer(Globals::ObjectID owner);
		virtual ~Initializer();

		virtual int Update(UpdateEvent* e, ParticleBuffer::Particle& particle) = 0;

		Initializer& operator=(const Initializer& rhs);
	};
}

