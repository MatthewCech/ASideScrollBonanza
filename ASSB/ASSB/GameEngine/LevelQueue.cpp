#include "LevelQueue.hpp"
#include "Globals.hpp"
#include "Events/UpdateEvent.hpp"
#include "FileSystem/LevelPreloadingMapper.hpp"
#include "GameEngine/GameEngine.h"
#include "Events/KeyboardEvent.hpp"



namespace ASSB
{
	// Static init
	LevelQueue *LevelQueue::Instance = nullptr;


	// Constructor
	LevelQueue::LevelQueue()
		: EventSystem::ObjectEventManager(Globals::EventSystemInstance)
		, pool_()
	{
		// Singleton management
		if (Instance == nullptr)
			Instance = this;
		else
			throw std::exception("One level queue please!");


		// Events
		Connect(this, &LevelQueue::update);
		Connect(this, &LevelQueue::keyboard);
	}


	// Level Queueing and associated
	void LevelQueue::AddToPool(std::string tag)
	{
		std::string res = FileSystem::LevelPreloadingMapper::Retrieve(tag);
		if(res.size() > 0)
			pool_.push_back(res);
	}

	// Loads the default level.
	void LevelQueue::LoadDefault()
	{
		FileSystem::LevelPreloadingMapper::LevelFromFile(FileSystem::LevelPreloadingMapper::Retrieve("default"));
	}

	// Reads in map
	void LevelQueue::BulkPopulate(const std::unordered_map<std::string, std::string> &map)
	{
		for (auto &item : map)
			pool_.push_back(item.second);
	}
	
	// Loads a random level from the pool
	void LevelQueue::loadRandom()
	{
		if(pool_.size() > 0)
			FileSystem::LevelPreloadingMapper::LevelFromFile(pool_[rand() % pool_.size()]);
	}

	// Update tick
	void LevelQueue::update(UpdateEvent *)
	{
		//GameEngine::Instance->Camera.
		if (GameEngine::Instance->Camera.GetPosition().X + 14 > FileSystem::LevelPreloadingMapper::CurrentOffset)
			if (FileSystem::LevelPreloadingMapper::CurrentOffset > 10)
				loadRandom();
			else
				LoadDefault();
	}


	//!TODO: CHEATS! TESTING AND WHATNOT
	void LevelQueue::keyboard(KeyboardEvent *e)
	{
		if (e->Down && e->Key == Key::L)
			loadRandom();

		if (e->Down && e->Key == Key::N)
			FileSystem::LevelPreloadingMapper::NukeObjects();
	}
}