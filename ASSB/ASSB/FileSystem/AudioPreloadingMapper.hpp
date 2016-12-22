#pragma once
#include "FileSystem/File.hpp"
#include "AudioSystem/AudioDefines.hpp"
#include <unordered_map>



namespace FileSystem
{
	// Preloads the sounds for the audio system and allows for retrieval
	class AudioPreloadingMapper
	{
	public:
		// Static Functions
		static void LoadFromFile(std::string filepath);

		// Member Functions
		static bool Associate(std::string tag, std::string path);
		static AudioFilePtr Retrieve(std::string tag);

	private:
		// Variables
		static std::unordered_map<std::string, AudioFilePtr> assciatedTags_;
	};
}
