#pragma once
#include "EventSystem/EventSystem.hpp"
#include "AudioSystem/AudioSystem.hpp"



namespace ASSB
{
	class Globals
	{
	public:
		// Global Variables
		static EventSystem::EventSystem EventSystemInstance;
		static AudioSystem::AudioSystem AudioSystemInstance; // arg is number of channels.
		typedef unsigned long long ObjectID;
	};
}
