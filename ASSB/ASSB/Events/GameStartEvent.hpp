#pragma once
#include "EventSystem/Event.hpp"


namespace ASSB
{
	// Stub class to be an event for starting the game (enable player, hide menu)
	class GameStartEvent : public EventSystem::Event
	{ public: };
}
