#include "LevelPreloader.hpp"
#include "AudioSystem/AudioDefines.hpp"
#include "Components/TransformComponent.h"
#include "Components/RigidBodyComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "GameEngine/GameEngine.h"
#include "FileSystem/ImagePreloadingMapper.hpp"
#include <cstdlib>



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
		const size_t commaLoc1 = first.find_first_of(",");
		if (commaLoc1 == std::string::npos)
			return false;

		const float x{ std::stof(first.substr(0, commaLoc1)) };
		const float y{ std::stof(first.substr(commaLoc1 + 1)) };

		// Split for image path and flags string
		const size_t commaLoc2 = second.find_first_of(",");
		if (commaLoc2 == std::string::npos)
			return false;

		std::string imageTag{ second.substr(0, commaLoc2) };
		const std::string flags{ second.substr(commaLoc2 + 1) };

		float scaleX = 1;
		float scaleY = 1;
		bool scaleSpecified = false;
		const size_t scaleLoc = second.find_first_of("*");
		if (scaleLoc != std::string::npos)
		{
			const std::string scaleStr{ imageTag.substr(scaleLoc + 1) };
			const size_t xCharLoc = scaleStr.find_first_of("x");
			if (xCharLoc == std::string::npos)
				return false;

			scaleX = std::stof(scaleStr.substr(0, xCharLoc));
			scaleY = std::stof(scaleStr.substr(xCharLoc + 1));
			imageTag = imageTag.substr(0, scaleLoc);
			scaleSpecified = true;
		}


    //!TODO: MOVE ALL PARSING ABOVE TO CUSTOM OBJECT

		// Construct components
		ASSB::Globals::ObjectID id = ASSB::GameEngine::Instance->CreateGameObject();
		ASSB::GameEngine::Instance->AddComponent<ASSB::RigidBodyComponent>(id);

		// Set position, and scale if specified.
		ASSB::ComponentHandle<ASSB::TransformComponent> tComp = ASSB::GameEngine::Instance->GetComponent<ASSB::TransformComponent>(id);
		tComp->SetPosition({ x, y, 0});
		if (scaleSpecified)
		{
			tComp->SetScale(scaleX, scaleY);
		}

		// Dynamic or static
		if (flags[0] == 'd')
		{
			ASSB::GameEngine::Instance->GetComponent<ASSB::RigidBodyComponent>(id)->SetStatic(false);

			//!TODO: For testing
			ASSB::GameEngine::Instance->GetComponent<ASSB::RigidBodyComponent>(id)->
				SetVelocity(Graphics::Vector4(
					static_cast<float>((((std::rand() % 100) - 50.0) / 50.0))
					, static_cast<float>((((std::rand() % 100) - 50.0) / 50.0))
					, static_cast<float>((((std::rand() % 100) - 50.0) / 50.0))));
		}
		else if (flags[0] == 's')
		{
			ASSB::GameEngine::Instance->GetComponent<ASSB::RigidBodyComponent>(id)->SetStatic(true);
		}

		// Set image
		std::string path = FileSystem::ImagePreloadingMapper::Retrieve(imageTag);
		if (path.size() > 0)
		{
			ASSB::GameEngine::Instance->GetComponent<ASSB::SpriteComponent>(id)->Path = std::wstring(path.begin(), path.end());
		}

		// Success(tm) if we made it here!
		return true;
	}
}
