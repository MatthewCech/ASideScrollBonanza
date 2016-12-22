#pragma once
#include "FileSystem\File.hpp"



namespace FileSystem
{
	// Preloads the sounds in the audio system
	class AudioPreloader
	{
	public:
		// Static Functions
		static void LoadFromFile(std::string filepath);
	};
}
