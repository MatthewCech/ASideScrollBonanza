#include "Graphics/Window.h"
#include "GameEngine/GameEngine.h"
#include "Components/SoundEmitterComponent.hpp"
#include "Events/UISelectEvent.hpp"
#include "FileSystem/AudioPreloadingMapper.hpp"
#include "FileSystem/ImagePreloadingMapper.hpp"
#include "FileSystem/LevelPreloader.hpp"
#include "Globals.hpp"



// Defines for testing
#define ASSB_AMI_ ASSB::Globals::AudioMapperInstance
#define ASSB_ESI_ ASSB::Globals::EventSystemInstance


int main()
{
	// Window and engine creation
	Graphics::Window window(L"OWO");
	ASSB::GameEngine Engine(window);

	// Preloading
	FileSystem::ImagePreloadingMapper::LoadFromFile("../../../Assets/Levels/ImageList.txt");
	FileSystem::AudioPreloadingMapper::LoadFromFile("../../../Assets/AudioList.txt");
	FileSystem::LevelPreloader::LoadFromFile("../../../Assets/Levels/LevelTest.txt");

	// Audio system test
	ASSB::SoundEmitterComponent se("Select1");
	se.PlayOnEvent<ASSB::UISelectionChangedEvent>();
	ASSB_ESI_.Dispatch(new ASSB::UISelectionChangedEvent());

	// Physics system test
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