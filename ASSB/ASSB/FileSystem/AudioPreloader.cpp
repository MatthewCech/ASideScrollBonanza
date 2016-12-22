#include "AudioPreloader.hpp"
#include "Globals.hpp"



namespace FileSystem
{
	// Static Functions
	void AudioPreloader::LoadFromFile(std::string filepath)
	{
		File f{ filepath };
		for (unsigned int i{ 0 }; i < f.GetLineCount(); ++i)
		{
			std::string line{ f[i] };
			size_t loc{ line.find_first_of(":") };

			std::string tag{ line.substr(0, loc) };
			std::string path{ line.substr(loc + 1) };

			ASSB::Globals::AudioMapperInstance.Associate(tag, path);
		}
	}
}
