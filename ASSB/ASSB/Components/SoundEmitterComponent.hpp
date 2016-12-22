#pragma once
#include "Component.hpp" // Component
#include "AudioSystem/AudioDefines.hpp"
#include "EventSystem/Event.hpp"



namespace ASSB
{
	class SoundEmitterComponent : public Component
	{
	public:
		// Constructor
		SoundEmitterComponent(std::string tag = "");

		// Member functions
		void Play();
		void Stop();
		void SetSource(std::string newTag);
		
		// Templatized Functions
		template <typename EventType> void PlayOnEvent();

	private:
		// Private variables
		AudioFilePtr af_;

		// Private Functions
		void eventCallback(EventSystem::Event *e);

		// Omit
		SoundEmitterComponent &operator=(const SoundEmitterComponent &rhs) = delete;
		SoundEmitterComponent(const SoundEmitterComponent *rhs) = delete;
	};
}

#include "SoundEmitterComponent.tpp"
