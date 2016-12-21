#include "GameEngine.h"

namespace ASSB
{
	GameEngine::GameEngine(Graphics::Window & window) : Window(window), Graphics(window)
	{
	}

	void GameEngine::Loop()
	{
		Graphics.ClearScreen();
		Graphics.Present();
	}
}
