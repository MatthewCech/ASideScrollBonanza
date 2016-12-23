#pragma once
#include "EventSystem/Event.hpp"


namespace ASSB
{
	// Event indicating the game has been paused or unpaused.
	class PauseToggleEvent : public EventSystem::Event
	{
	public:
		PauseToggleEvent(bool isPaused) : Paused(isPaused) { }
	  bool Paused;
	};
}
