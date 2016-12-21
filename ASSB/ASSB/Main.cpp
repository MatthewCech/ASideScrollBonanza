#include "Graphics/Window.h"
#include "GameEngine/GameEngine.h"
#include "Globals.hpp"



int main()
{
	Graphics::Window window(L"OWO");
	ASSB::GameEngine Engine(window);

	// Events thing
	EventSystem::Event e;

  // Test audio system
	// Globals "../../../Assets/Audio/Confirm1.wav" };
	ASSB::Globals::AudioMapperInstance.Associate(
		"Confirm1", "../../../Assets/Audio/Confirm1.wav");
  // a.PreloadFile(af);
  // a.PlayFile(af, true);

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