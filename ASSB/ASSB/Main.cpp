#include "Graphics/Window.h"
#include "GameEngine/GameEngine.h"
#include "Globals.hpp"
#include "SoundEmitterComponent.hpp"
#include "Events\UISelectEvent.hpp"
#include "FileSystem\AudioPreloader.hpp"


// Defines for testing
#define ASSB_AMI_ ASSB::Globals::AudioMapperInstance
#define ASSB_ESI_ ASSB::Globals::EventSystemInstance


int main()
{
	Graphics::Window window(L"OWO");
	ASSB::GameEngine Engine(window);

	// Events thing
	EventSystem::Event e;

	// Audiosystem Test
	FileSystem::AudioPreloader::LoadFromFile("../../../Assets/AudioList.txt");
	ASSB::SoundEmitterComponent se("Select1");
	se.PlayOnEvent<ASSB::UISelectEvent>();
	ASSB_ESI_.Dispatch(new ASSB::UISelectEvent());

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