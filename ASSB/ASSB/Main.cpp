#include "Graphics/Window.h"
#include "GameEngine/GameEngine.h"

int main()
{
	Graphics::Window window(L"OWO");
	ASSB::GameEngine Engine(window);
	

	bool run = true;
	MSG msg;
	while (run)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				run = false;
		}

		Engine.Loop();
	}


	return 0;
}