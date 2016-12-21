#pragma once
#include <unordered_map>
#include "Graphics/GraphicsEngine.h"


namespace ASSB
{
	typedef unsigned long long ObjectID;

	class GameEngine
	{
	public:
		GameEngine(Graphics::Window& window);

		ObjectID GetIdOf(const std::string name);

		void Loop();
	private:
		bool Running;
		Graphics::GraphicsEngine Graphics;
		Graphics::Window& Window;
		std::unordered_map<std::string, ObjectID> GameObjects;

		GameEngine(const ASSB::GameEngine& other) = delete;

		GameEngine& operator=(const GameEngine& other) = delete;

	};
}
