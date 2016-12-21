#include "Graphics/Window.h"
#include "GameEngine/GameEngine.h"
#include "Events/Event.hpp"


int main()
{
	Graphics::Window window(L"OWO");
	ASSB::GameEngine Engine(window);
	
  // Events thing
  Events::Event e;

	bool run = true;
	MSG msg;

  // Primary loop
	while (run)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				run = false;
		}

		Engine.UpdateCamera();
		Engine.Loop();
	}


	return 0;
}