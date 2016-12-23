#pragma once
#include <unordered_map>
#include <vector>
#include "EventSystem/ObjectEventManager.hpp"
#include <string>
#include <unordered_map>


namespace ASSB
{
	/*/
	class Level
	{
	public:
		Level(int number) : Number(number);
		int Number;

	private:
		std::vector<std::string> sections_;
	};*/
	class UpdateEvent;
	class KeyboardEvent;
	class LevelQueue : public EventSystem::ObjectEventManager
	{
	public:
		// Constructor
		LevelQueue();

		// Level Queueing and associated
		void AddToPool(std::string tag);
		void BulkPopulate(const std::unordered_map<std::string, std::string> &map);
		void LoadDefault();

		// Singleton instance
		static LevelQueue *Instance;

	public:
		// Variables
		std::vector<std::string> pool_;
		void update(UpdateEvent *e);
		void keyboard(KeyboardEvent *e);
		void loadRandom();

		// Omit
		LevelQueue(const LevelQueue &rhs) = delete;
		LevelQueue &operator=(const LevelQueue &rhs) = delete;
	};
}
