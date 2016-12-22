#include "Globals.hpp"


namespace ASSB
{
	// Static initialization of globals
	EventSystem::EventSystem Globals::EventSystemInstance{ EventSystem::EventSystem() };
	AudioSystem::AudioSystem Globals::AudioSystemInstance{ AudioSystem::AudioSystem(20) }; // arg is number of channels
}