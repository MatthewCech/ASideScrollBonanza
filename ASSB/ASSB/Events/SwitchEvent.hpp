#pragma once
#include "EventSystem/Event.hpp"


namespace ASSB
{
	// Event indicating the game has been paused or unpaused.
	class SwitchEvent : public EventSystem::Event
	{
	public:
		SwitchEvent(bool white) : White(white) { }
		bool White;
	};
}