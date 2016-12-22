#pragma once
#include <unordered_map>



namespace FileSystem
{
	// A combination of a class that preloads and sets up a map based on
	// a specified file.
	class ImagePreloadingMapper
	{
	public:
		// Member Functions
		static void LoadFromFile(std::string filepath);
		static bool Associate(std::string tag, std::string path);
		static std::string Retrieve(std::string tag);

	private:
		// Variables
		static std::unordered_map<std::string, std::string> associatedStrings_;
	};
}
