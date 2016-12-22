#include "AudioMapper.hpp"
#include "Globals.hpp"



namespace AudioSystem
{
	// Statics
	bool AudioMapper::instanciated_ = false;


	// Constructor
	AudioMapper::AudioMapper() 
		: assciatedTags_()
	{
		DEBUG_PRINT("Audio Mapper was made!");

		//if (instanciated_)
		//	throw "Don't.";
		//else
		//	instanciated_ = true;
	}


	// Associates a tag/name with a specific audio path.
	// This tag can be used for lookup later, and the path to the audio
	// is taken and has an object instanciated for it.
	// Tags must be unique, otherwise the most recent tag will override
	// the last one.
	bool AudioMapper::Associate(std::string tag, std::string path)// , AudioSystem &a)
	{
		// If we don't have a tag,
		if (assciatedTags_.find(tag) == assciatedTags_.end())
		{
			AudioFilePtr af = std::make_shared<AudioFile>(path);
			if (ASSB::Globals::AudioSystemInstance.PreloadFile(*af))
				assciatedTags_[tag] = af;
			else
				DEBUG_PRINT("Audio Object could not be created with specified path!");

			return true;
		}
		else
			DEBUG_PRINT("Attempted to register the same tag twice!");

		return false;
	}


	// Returns a pointer to the loaded audio file associated with the unique tag.
	AudioFilePtr AudioMapper::Retrieve(std::string tag)
	{
		return assciatedTags_.at(tag);
	}
}