#pragma once
#include "EventSystem\Event.hpp"
#include "GameEngine/GameTime.h"


namespace ASSB
{
	// An event for 
	class UpdateEvent : public EventSystem::Event
	{
	public:
		UpdateEvent(GameTime time) : Time(time) {}

		GameTime Time;
	private:
	};
}