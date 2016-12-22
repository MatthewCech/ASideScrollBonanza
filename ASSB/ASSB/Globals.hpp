#pragma once
#include "EventSystem\EventSystem.hpp"
#include "AudioSystem\AudioSystem.hpp"
#include "AudioSystem\AudioMapper.hpp"
//#include "PhsyicsSystem\PhysicsSystem.hpp"


namespace ASSB
{
	class Globals
	{
	public:
		// Global Variables
		static EventSystem::EventSystem EventSystemInstance;
		static AudioSystem::AudioSystem AudioSystemInstance; // arg is number of channels.
		static AudioSystem::AudioMapper AudioMapperInstance;
		typedef unsigned long long ObjectID;
	};
}
