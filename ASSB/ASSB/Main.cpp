#include "Graphics/Window.h"
#include "GameEngine/GameEngine.h"
#include "Components/SoundEmitterComponent.hpp"
#include "Components/MenuManagerComponent.hpp"
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
	FileSystem::ImagePreloadingMapper::LoadFromFile("../../../Assets/ImageList.txt");
	FileSystem::AudioPreloadingMapper::LoadFromFile("../../../Assets/AudioList.txt");
	FileSystem::LevelPreloader::LoadFromFile("../../../Assets/Levels/LevelTest.txt");
	FileSystem::LevelPreloader::LoadFromFile("../../../Assets/Levels/SandboxLevel.txt");

	// Menu System
	ASSB::Globals::ObjectID obj = Engine.CreateGameObject();
	Engine.AddComponent<ASSB::MenuManagerComponent>(obj);
	ASSB::ComponentHandle<ASSB::MenuManagerComponent> comp = Engine.GetComponent<ASSB::MenuManagerComponent>(obj);
	comp->SetSpacing({ 0, .5f, 0 });
	comp->SetPosition({ 0, 1, 0 });
	comp->SetIndicatorTag("selectImage", { 1.75f, .4f, 0 });
	comp->AddInteractable("buttonBase", { 1.5f,.3f,0 }, new ASSB::UISelectionChangedEvent());
	comp->AddInteractable("buttonBase", { 1.5f,.3f,0 }, new ASSB::UISelectionChangedEvent());
	comp->AddInteractable("buttonBase", { 1.5f,.3f,0 }, new ASSB::UISelectionChangedEvent());
	
	//Engine.AddComponent<
	UNUSED(obj);
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