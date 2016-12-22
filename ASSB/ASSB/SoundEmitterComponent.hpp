#pragma once
#include "Component.hpp" // Component
#include "AudioSystem\AudioDefines.hpp"


namespace ASSB
{
	class SoundEmitterComponent : public Component
	{
	public:
		// Constructor
		SoundEmitterComponent(std::string tag);
		void Play();
		void Stop();
		void SetSource(std::string newTag);

	private:
		// Variables
		AudioFilePtr af_;

		// Omit
		SoundEmitterComponent &operator=(const SoundEmitterComponent &rhs) = delete;
		SoundEmitterComponent(const SoundEmitterComponent *rhs) = delete;
	};
}