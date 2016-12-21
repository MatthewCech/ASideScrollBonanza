#pragma once
#include "EventSystem\EventSystem.hpp"



namespace ASSB
{
	namespace Globals
	{
		// Global Variables
		static EventSystem::EventSystem EventSystemInstance = EventSystem::EventSystem();
		typedef unsigned long long ObjectID;
	}
}
