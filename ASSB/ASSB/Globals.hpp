#pragma once
#include "EventSystem\EventSystem.hpp"
#include "AudioSystem\AudioSystem.hpp"
#include "AudioSystem\AudioMapper.hpp"

namespace ASSB
{
	namespace Globals
	{
		// Global Variables
		static EventSystem::EventSystem EventSystemInstance{ EventSystem::EventSystem()   };
		static AudioSystem::AudioSystem AudioSystemInstance{ AudioSystem::AudioSystem(20) }; // arg is number of channels.
		static AudioSystem::AudioMapper AudioMapperInstance{ AudioSystem::AudioMapper()   };
		typedef unsigned long long ObjectID;
	}
}
