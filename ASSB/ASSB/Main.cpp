#include "Graphics/Window.h"
#include "GameEngine/GameEngine.h"
#include "Globals.hpp"
#include "SoundEmitterComponent.hpp"


#define ASSB_AMI_ ASSB::Globals::AudioMapperInstance

int main()
{
	Graphics::Window window(L"OWO");
	ASSB::GameEngine Engine(window);

	// Events thing
	EventSystem::Event e;

  // Test audio system
	//AMI_.Associate("Confirm1", "../../../Assets/SFX/Confirm1.wav");
	//AMI_.Associate("Switch1", "../../../Assets/SFX/Switch1.wav");
	//AMI_.Associate("Select1", "../../../Assets/SFX/Select1.wav");
	//ASSB_AMI_.Associate("Confirm", "../../../Assets/Music/TESTING.wav");
	ASSB_AMI_.Associate("Confirm", "../../../Assets/SFX/Confirm1.wav");
	//
	//ASI_.PlayFile(*AMI_.Retrieve("SONG"));
	//ASI_.PlayFile(*AMI_.Retrieve("Switch1"));
	//ASI_.PlayFile(*AMI_.Retrieve("Select1"));
	//ASI_.PlayFile(*AMI_.Retrieve("Confirm1"));
	ASSB::SoundEmitterComponent se("Confirm");
	se.Play();

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