#include "AudioPreloadingMapper.hpp"
#include "Globals.hpp"
#include "AudioSystem/AudioDefines.hpp"
#include "AudioSystem/AudioFile.hpp"
#include <memory>



namespace FileSystem
{
	// Static initialization
	std::unordered_map<std::string, AudioFilePtr> AudioPreloadingMapper::assciatedTags_{ std::unordered_map<std::string, AudioFilePtr>() };


	// Associates a tag/name with a specific audio path.
	// This tag can be used for lookup later, and the path to the audio
	// is taken and has an object instanciated for it.
	// Tags must be unique, otherwise the most recent tag will override
	// the last one.
	bool AudioPreloadingMapper::Associate(std::string tag, std::string path)// , AudioSystem &a)
	{
		// If we don't have a tag,
		if (assciatedTags_.find(tag) == assciatedTags_.end())
		{
			AudioFilePtr af = std::make_shared<AudioSystem::AudioFile>(path);
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
	AudioFilePtr AudioPreloadingMapper::Retrieve(std::string tag)
	{
		if (tag.size() > 0)
			return assciatedTags_.at(tag);

		return nullptr;
	}


	// Attempts to parse a file of tag:path audio asset pairs in a specified file.
	// Will continue to parse until the end of the file or invalid line is hit.
	void AudioPreloadingMapper::LoadFromFile(std::string filepath)
	{
		File f{ filepath };
		if (!f.FileFound())
		{
			DEBUG_PRINT("Could not find file specified for Level Preloader at: " << filepath);
			return;
		}

		// Loop over each line, attempt to add tag:path pair to Audio Mapper.
		for (unsigned int i{ 0 }; i < f.GetLineCount(); ++i)
		{
			std::string line{ f[i] };
			size_t loc{ line.find_first_of(":") };
			if (loc == std::string::npos)
			{
				DEBUG_PRINT("Could not parse out :, assuming requested EOF.");
				DEBUG_PRINT("Line parse attempt on: " << line);
				return;
			}

			std::string tag{ line.substr(0, loc) };
			std::string path{ line.substr(loc + 1) };
			Associate(tag, path);
		}
	}
}
