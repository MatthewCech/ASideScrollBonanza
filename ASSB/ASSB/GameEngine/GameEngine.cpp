#include "GameEngine.h"

namespace ASSB
{
	GameEngine::GameEngine(Graphics::Window & window) : Window(window), Graphics(window) {}

	ObjectID GameEngine::GetIdOf(const std::string name)
	{
		//check if it exists
		if (GameObjects.find(name) == GameObjects.end())
			return NULL;
		else
			return GameObjects[name];
	}

	void GameEngine::Loop()
	{
		Graphics.ClearScreen();
		Graphics.Present();
	}
}
