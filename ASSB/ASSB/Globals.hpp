#pragma once
#include "EventSystem\EventSystem.hpp"
#include "AudioSystem\AudioSystem.hpp"


namespace ASSB
{
	namespace Globals
	{
		// Global Variables
		static EventSystem::EventSystem EventSystemInstance = EventSystem::EventSystem();
		static AudioSystem::AudioSystem AudioSystemInstance = AudioSystem::AudioSystem(20); // arg is channel number
		typedef unsigned long long ObjectID;
	}
}
