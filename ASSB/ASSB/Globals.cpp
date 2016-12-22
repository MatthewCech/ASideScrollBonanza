#include "Globals.hpp"


namespace ASSB
{
	EventSystem::EventSystem Globals::EventSystemInstance{ EventSystem::EventSystem() };
	AudioSystem::AudioSystem Globals::AudioSystemInstance{ AudioSystem::AudioSystem(20) };
	AudioSystem::AudioMapper Globals::AudioMapperInstance{ AudioSystem::AudioMapper()   };
}