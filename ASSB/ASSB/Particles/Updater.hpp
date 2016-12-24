#pragma once

#include "Events/UpdateEvent.hpp"
#include "EventSystem/ObjectEventManager.hpp"
#include "Globals.hpp"
#include "GameEngine/ComponentHandle.h"
#include "Components/ParticleComponent.hpp"

namespace ASSB
{
	class Updater : public EventSystem::ObjectEventManager
	{
	public:
		Globals::ObjectID Owner;
		ComponentHandle<ParticleComponent> Comp;

		Updater(Globals::ObjectID owner);
		virtual ~Updater();

		virtual int Update(UpdateEvent* e, ParticleBuffer::Particle& particle) = 0;

		Updater& operator=(const Updater& rhs);
	};
}

