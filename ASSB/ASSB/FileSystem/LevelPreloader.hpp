#pragma once
#include "FileSystem\File.hpp"
#include <string>


namespace FileSystem
{
	// Preloads a given level in the engine
	class LevelPreloader
	{
	public:
		// Static Functions
		static void LoadFromFile(std::string filepath);
		static bool ParseLine(std::string line);
	};
}
