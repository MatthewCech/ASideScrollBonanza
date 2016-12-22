#pragma once
#include "MouseButton.h"

namespace ASSB
{
	struct MouseState
	{
		float DeltaScroll;
		short ScreenXPos;
		short ScreenYPos;

		MouseState();

		void SetButtonDown(MouseButton button, bool down);
		bool IsButtonDown(MouseButton button);
	private:
		unsigned char ButtonState;
	};
}
