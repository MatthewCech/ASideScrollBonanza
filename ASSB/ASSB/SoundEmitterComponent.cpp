#include "SoundEmitterComponent.hpp"
#include "Globals.hpp"

// For testing
#define SE_AMI_ ASSB::Globals::AudioMapperInstance
#define SE_ASI_ ASSB::Globals::AudioSystemInstance



namespace ASSB
{
	// Constructor
	SoundEmitterComponent::SoundEmitterComponent(std::string tag)
		: af_(SE_AMI_.Retrieve(tag))
	{  }

	
	// Play the sound
	void SoundEmitterComponent::Play()
	{
		SE_ASI_.PlayFile(*af_);
	}


	// Stops the sound emitter
	void SoundEmitterComponent::Stop()
	{
		SE_ASI_.StopFile(*af_);
	}


	// Sets the name of the audio file to get.
	// This is a tag, not the actual full path.
	void SoundEmitterComponent::SetSource(std::string newTag)
	{
		Stop();
		af_ = SE_AMI_.Retrieve(newTag);
	}


	// Event callback
	void SoundEmitterComponent::eventCallback(EventSystem::Event *e)
	{
		Play();
		UNUSED(e);
	}
}

#undef SE_AMI_
#undef SE_ASI_

