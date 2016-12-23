#pragma once
#include "EventSystem/Event.hpp"



namespace ASSB
{
	// A stub event to specify we have requested to exit, but have not confirmed yet.
	class QuitRequestEvent : public EventSystem::Event
	{ public: };
}
