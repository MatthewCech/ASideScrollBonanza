#pragma once
#include "Events/UpdateEvent.hpp"
#include "EventSystem/ObjectEventManager.hpp"
#include "Globals.hpp"
#include "GameEngine/ComponentHandle.h"
#include "Components/ParticleComponent.hpp"

namespace ASSB
{
	class Emitter : public EventSystem::ObjectEventManager
	{
	public:
		Globals::ObjectID Owner;
		ComponentHandle<ParticleComponent> Comp;

		Emitter(Globals::ObjectID owner);
		virtual ~Emitter();

		virtual int Update(UpdateEvent* e) = 0;

		Emitter& operator=(const Emitter& rhs);
	};
}
