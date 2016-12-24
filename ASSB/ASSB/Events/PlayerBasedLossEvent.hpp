#pragma once
#include "EventSystem/Event.hpp"



namespace ASSB
{
	// Specific derived event to sigify a shutdown request.
	class PlayerBasedLossEvent : public EventSystem::Event
	{  };
}

