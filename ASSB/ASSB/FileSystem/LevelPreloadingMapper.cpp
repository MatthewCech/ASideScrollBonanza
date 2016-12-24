#include "LevelPreloadingMapper.hpp"
#include "AudioSystem/AudioDefines.hpp"
#include "Components/TransformComponent.h"
#include "Components/RigidBodyComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "GameEngine/GameEngine.h"
#include "FileSystem/ImagePreloadingMapper.hpp"
#include "AudioSystem/AudioDefines.hpp"
#include <cstdlib>



namespace FileSystem
{
	// Static initialization
	unsigned long long LevelPreloadingMapper::CurrentOffset = 0;
	std::unordered_map<std::string, std::string> LevelPreloadingMapper::associatedStrings_ = std::unordered_map<std::string, std::string>();
	std::queue<ASSB::Globals::ObjectID> LevelPreloadingMapper::loadedHistory_ = std::queue<ASSB::Globals::ObjectID>();


	// Associate tags
	bool LevelPreloadingMapper::Associate(std::string tag, std::string path)// , AudioSystem &a)
	{
		// Associate
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
	std::string LevelPreloadingMapper::Retrieve(std::string tag)
	{
		const auto iter = associatedStrings_.find(tag);
		if (iter == associatedStrings_.end())
		{
			DEBUG_PRINT("Invalid tag lookup in Level Mapper!");
			return "";
		}
		else
			return iter->second;
	}


	// Load from a file
	void LevelPreloadingMapper::LoadFromFile(std::string filepath)
	{
		File f{ filepath };
		if (!f.FileFound())
		{
			DEBUG_PRINT("Could not find file specified for Level Preloader&Mapper at: " << filepath);
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


	// Attempts to generate information for a level based on a filepath.
	void LevelPreloadingMapper::LevelFromFile(std::string filepath, bool automaticOffset, unsigned long long offsetX)
	{
		File f{ filepath };
		if (!f.FileFound())
		{
			DEBUG_PRINT("Level file invalid path at: " << filepath);
			return;
		}

		if (automaticOffset)
			offsetX = CurrentOffset;

		int width = 0;
		for (unsigned int i{ 0 }; i < f.GetLineCount(); ++i)
		{
			std::string line = f[i];
			if(!ParseLine(line, offsetX, width))
			{
				DEBUG_PRINT("Could not parse line, assuming requested EOF.");
				DEBUG_PRINT("Line parse attempt on: " << line);
				return;
			}
		}

		if(automaticOffset)
			CurrentOffset += width;
	}


	// Parses an individual line into objects, just returns success or not.
	bool LevelPreloadingMapper::ParseLine(std::string line, unsigned long long offsetX, int &width)
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

		// Get X and Y, update furthest if necessary
		float x{ std::stof(first.substr(0, commaLoc1)) };
		const float y{ std::stof(first.substr(commaLoc1 + 1)) };
		if( x > width)
			width = static_cast<int>(x);
		x += static_cast<float>(offsetX);

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

		// Set position, and scale if specified.
		ASSB::ComponentHandle<ASSB::TransformComponent> tComp = ASSB::GameEngine::Instance->GetComponent<ASSB::TransformComponent>(id);
		tComp->SetPosition({ x, y, 0});
		if (scaleSpecified)
		{
			tComp->SetScale(scaleX, scaleY);
		}

		// Handle flags
		bool rbHasCreated = false;
		for (size_t i = 0; i < flags.size(); ++i)
		{
			const char flag = flags[i];
			if (rbHasCreated)
			{
				ASSB::ComponentHandle<ASSB::RigidBodyComponent> rigidBody = ASSB::GameEngine::Instance->GetComponent<ASSB::RigidBodyComponent>(id);
				if (flag == 'd')
					rigidBody->SetStatic(false);
				else if (flag == 's')
					rigidBody->SetStatic(true);
				else if (flag == 'n')
					rigidBody->SetCollisionType(ASSB::NO_COLLISION);
			}
			else
			{
				if (flag == 'g' || flag == 'c')
				{
					ASSB::GameEngine::Instance->AddComponent<ASSB::RigidBodyComponent>(id);
					ASSB::ComponentHandle<ASSB::RigidBodyComponent> rigidBody = ASSB::GameEngine::Instance->GetComponent<ASSB::RigidBodyComponent>(id);
					rigidBody->SetStatic(true);
					if(flag == 'g')
						rigidBody->SetCollisionType(ASSB::GHOSTING);
					if (flag == 'c')
						rigidBody->SetCollisionType(ASSB::COLLIDABLE);
					rbHasCreated = true;
				}
			}
		}

		// Set image
		size_t tickLoc = imageTag.find_first_of("'");
		if (tickLoc != std::string::npos)
		{
			std::string dark = FileSystem::ImagePreloadingMapper::Retrieve(imageTag.substr(0, tickLoc));
			std::string light = FileSystem::ImagePreloadingMapper::Retrieve(imageTag.substr(tickLoc + 1));
			if (light.size() > 0)
				if (dark.size() > 0)
				{
					ASSB::ComponentHandle<ASSB::SpriteComponent> spriteComp = ASSB::GameEngine::Instance->GetComponent<ASSB::SpriteComponent>(id);
					spriteComp->AddPath(std::wstring(light.begin(), light.end()));
					spriteComp->AddAltPath(std::wstring(dark.begin(), dark.end()));
					spriteComp->SetSwappable(true);
				}
		}
		else
		{
			std::string path = FileSystem::ImagePreloadingMapper::Retrieve(imageTag);
			if (path.size() > 0)
			{
				ASSB::GameEngine::Instance->GetComponent<ASSB::SpriteComponent>(id)->AddPath(std::wstring(path.begin(), path.end()));
			}
		}

		// Success(tm) if we made it here!
		loadedHistory_.push(id);
		return true;
	}

	void LevelPreloadingMapper::resetPosition()
	{
		CurrentOffset = 0;
	}

	void LevelPreloadingMapper::NukeObjects()
	{
		while (loadedHistory_.size() > 0)
		{
			ASSB::GameEngine::Instance->RemoveID(loadedHistory_.front());
			loadedHistory_.pop();
		}

		resetPosition();
	}

	void LevelPreloadingMapper::CheckOldestLoaded()
	{
		if (loadedHistory_.size() == 0)
			return;

		ASSB::Globals::ObjectID id = loadedHistory_.front();
		ASSB::Globals::ObjectID playerID = ASSB::GameEngine::Instance->GetIdOf("player");
		ASSB::ComponentHandle<ASSB::TransformComponent> trID = ASSB::GameEngine::Instance->GetComponent<ASSB::TransformComponent>(id);
		ASSB::ComponentHandle<ASSB::TransformComponent> trPlayer = ASSB::GameEngine::Instance->GetComponent<ASSB::TransformComponent>(playerID);
		if (trID->GetPosition().X < trPlayer->GetPosition().X - 2)
		{
			ASSB::GameEngine::Instance->RemoveID(id);
			loadedHistory_.pop();
		}
	}

	// Dumps all tags
	const std::unordered_map<std::string, std::string> &LevelPreloadingMapper::DumpTags()
	{
		return associatedStrings_;
	}
}
