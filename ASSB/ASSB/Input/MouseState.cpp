#include "MouseState.h"

namespace ASSB
{
	MouseState::MouseState()
		: DeltaScroll(0)
		, ButtonState(0)
		, ScreenXPos(0)
		, ScreenYPos(0)
	{

	}

	void MouseState::SetButtonDown(MouseButton button, bool down)
	{
		if (down)
			ButtonState |= button;
		else
			ButtonState &= ~button;
	}

	bool MouseState::IsButtonDown(MouseButton button)
	{
		return (ButtonState & button) != 0;
	}
}
