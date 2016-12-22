#include "AudioPreloader.hpp"
#include "Globals.hpp"
#include "AudioSystem\AudioDefines.hpp"



namespace FileSystem
{
	// Attempts to parse a file of tag:path audio asset pairs in a specified file.
	// Will continue to parse until the end of the file or invalid line is hit.
	void AudioPreloader::LoadFromFile(std::string filepath)
	{
		File f{ filepath };
		if (!f.FileFound())
		{
			DEBUG_PRINT("Could not find file specified for Audio Preloader at: " << filepath);
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
				DEBUG_PRINT("Line parsed: " << line);
				return;
			}

			std::string tag{ line.substr(0, loc) };
			std::string path{ line.substr(loc + 1) };

			ASSB::Globals::AudioMapperInstance.Associate(tag, path);
		}
	}
}
