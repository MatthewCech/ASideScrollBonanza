#pragma once
#include "EventSystem/Event.hpp"
#include "GameEngine/GameTime.h"

namespace ASSB
{
	// An event designed to signify user input.
	class LoseEvent : public EventSystem::Event
	{
	public:
		// Constructor
		LoseEvent(GameTime time) : Time(time) { }

		// Variables
		GameTime Time;
	};
}