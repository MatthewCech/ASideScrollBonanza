#pragma once
#include "AudioFile.hpp"
#include "AudioSystem.hpp"
#include <string>
#include <unordered_map>



namespace ASSB
{
	class AudioMapper
	{
	public:
		// Constructor
		AudioMapper();
		~AudioMapper();

		// Member Functions
		void Associate(std::string tag, std::string path);
		AudioSystem::AudioFile *Retrieve(std::string tag);
	  
	private:
		// Variables
		std::unordered_map<std::string, AudioSystem::AudioFile *> assciatedTags_;
		
		// Omission
		AudioMapper(const AudioMapper &rhs) = delete;
		AudioMapper &operator=(const AudioMapper &rhs) = delete;
	};
}
