#include "Graphics/Window.h"

int main()
{
	Graphics::Window window(L"OWO");

	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0))
	{

	}

	return 0;
}