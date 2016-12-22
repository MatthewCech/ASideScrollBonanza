#include "LevelPreloader.hpp"
#include "AudioSystem/AudioDefines.hpp"
#include "Components/TransformComponent.h"
#include "Components/RigidBodyComponent.hpp"


namespace FileSystem
{
	// Attempts to generate information for a level based on a filepath.
	void LevelPreloader::LoadFromFile(std::string filepath)
	{
		File f{ filepath };
		if (!f.FileFound())
		{
			DEBUG_PRINT("Could not find file specified for Level Preloader at: " << filepath);
			return;
		}

		for (unsigned int i{ 0 }; i < f.GetLineCount(); ++i)
		{
			std::string line = f[i];
			if(!ParseLine(line))
			{
				DEBUG_PRINT("Could not parse line, assuming requested EOF.");
				DEBUG_PRINT("Line parse attempt on: " << line);
				return;
			}
		}
	}


	// Parses an individual line into objects, just returns success or not.
	bool LevelPreloader::ParseLine(std::string line)
	{
		// Split for block type and pos
		const size_t splitLoc = line.find_first_of(":");
		if (splitLoc == std::string::npos)
			return false;

		const std::string first{ line.substr(0, splitLoc) };
		const std::string second{ line.substr(splitLoc + 1) };

		// Split for position x and y
		size_t commaLoc = first.find_first_of(",");
		if (commaLoc == std::string::npos)
			return false;

		const float x{ std::stof(first.substr(0, commaLoc)) };
		const float y{ std::stof(first.substr(commaLoc + 1)) };


		// Construct components
		ASSB::TransformComponent t;
		t.SetPosition({ x, y, 0});
		ASSB::RigidBodyComponent r;
		r.SetStatic(true);
		//!TODO: Sprite component(s)

		// Success(tm) if we made it here!
		return true;
	}
}
