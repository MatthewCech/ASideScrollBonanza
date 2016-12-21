#pragma once
#include <thread>
#include "Graphics/GraphicsEngine.h"

namespace ASSB
{
	class GameEngine
	{
	public:

		GameEngine(Graphics::Window& window);

		void Loop();
	private:
		bool Running;
		std::thread LoopThread;
		Graphics::GraphicsEngine Graphics;
		Graphics::Window& Window;

		GameEngine(const ASSB::GameEngine& other) = delete;

		GameEngine& operator=(const GameEngine& other) = delete;

	};
}
