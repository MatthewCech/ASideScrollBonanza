#pragma once
#include "EventSystem/Event.hpp"



namespace ASSB
{
	// Specific derived event to sigify a shutdown request.
	class ShutdownEvent : public EventSystem::Event
	{  };
}
