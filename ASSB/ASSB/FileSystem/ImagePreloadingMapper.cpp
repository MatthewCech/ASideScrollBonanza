#include "ImagePreloadingMapper.hpp"
#include "AudioSystem/AudioDefines.hpp"
#include "File.hpp"



namespace FileSystem
{
	// Static initialization
	std::unordered_map<std::string, std::string> ImagePreloadingMapper::associatedStrings_{ std::unordered_map<std::string, std::string>() };


	// Attempts to parse a file of tag:path Asset pairs in a specified file.
  // Will continue to parse until the end of the file or invalid line is hit.
  void ImagePreloadingMapper::LoadFromFile(std::string filepath)
	{
		File f{ filepath };
		if (!f.FileFound())
		{
			DEBUG_PRINT("Could not find file specified for Asset Preloader&Mapper at: " << filepath);
			return;
		}

		// Loop over each line, attempt to associate via corresponding member function.
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


	// Asscoaites a unique tag with a path.
	bool ImagePreloadingMapper::Associate(std::string tag, std::string path)
	{
		if (associatedStrings_.find(tag) == associatedStrings_.end())
		{
			associatedStrings_[tag] = path;
			return true;
		}
		else
			DEBUG_PRINT("Attempted to register the same tag twice!");

		return false;
	}


	// Retrieve the path for an existing tag
	std::string ImagePreloadingMapper::Retrieve(std::string tag)
	{
		const auto iter = associatedStrings_.find(tag);
		if (iter == associatedStrings_.end())
		{
			DEBUG_PRINT("Invalid tag lookup in Image Mapper!");
			return "";
		}
		else
			return iter->second;
	}
}
