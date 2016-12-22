#include "SoundEmitterComponent.hpp"
#include "Globals.hpp"
#include "FileSystem/AudioPreloadingMapper.hpp"

// For testing
#define SE_ASI_ ASSB::Globals::AudioSystemInstance



namespace ASSB
{
	// Constructor
	SoundEmitterComponent::SoundEmitterComponent(std::string tag)
		: af_(FileSystem::AudioPreloadingMapper::Retrieve(tag))
	{  }

	
	// Play the sound
	void SoundEmitterComponent::Play()
	{
		if(af_ != nullptr)
			SE_ASI_.PlayFile(*af_);
	}


	// Stops the sound emitter
	void SoundEmitterComponent::Stop()
	{
		if(af_ != nullptr)
			SE_ASI_.StopFile(*af_);
	}


	// Sets the name of the audio file to get.
	// This is a tag, not the actual full path.
	void SoundEmitterComponent::SetSource(std::string newTag)
	{
		Stop();
		af_ = FileSystem::AudioPreloadingMapper::Retrieve(newTag);
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

