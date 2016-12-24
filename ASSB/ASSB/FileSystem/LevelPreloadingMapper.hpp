#pragma once
#include "FileSystem\File.hpp"
#include <string>
#include <unordered_map>


namespace FileSystem
{
	// Preloads a given level in the engine
	class LevelPreloadingMapper
	{
	public:
		// Static Functions
		static void LoadFromFile(std::string filepath);
		static void LevelFromFile(std::string filepath, bool automaticOffset = true, unsigned long long offsetX = 0);
		static unsigned long long CurrentOffset;
		static bool Associate(std::string tag, std::string path);
		static std::string Retrieve(std::string tag);
		static const std::unordered_map<std::string, std::string> &DumpTags();
		static void ResetPosition();

	private:
		// Variables
		static bool ParseLine(std::string line, unsigned long long offsetX, int &width);
		static std::unordered_map<std::string, std::string> associatedStrings_;
	};
}
