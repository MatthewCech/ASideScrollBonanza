#pragma once
#include "AudioFile.hpp"
#include "AudioSystem.hpp"
#include <string>
#include <unordered_map>



namespace AudioSystem
{
	class AudioMapper
	{
	public:
		// Constructor
		AudioMapper();
		
		// Member Functions
		bool Associate(std::string tag, std::string path);
		AudioFilePtr Retrieve(std::string tag);
	  
	private:
		// Variables
		std::unordered_map<std::string, AudioFilePtr> assciatedTags_;
	};
}
