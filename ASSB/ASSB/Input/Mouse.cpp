#include "Mouse.h"
#include "Globals.hpp"
#include "Events/MouseEvents.h"

namespace ASSB
{
	MouseState Mouse::Current;
	MouseState Mouse::Last;
	std::queue<MouseButton> Mouse::buttonsDown;
	std::queue<MouseButton> Mouse::buttonsUp;

	bool Mouse::IsButtonDown(MouseButton button)
	{
		return Current.IsButtonDown(button);
	}

	bool Mouse::WasButtonPressed(MouseButton button)
	{
		return Current.IsButtonDown(button) && !Last.IsButtonDown(button);
	}

	LRESULT Mouse::Scroll(UINT /*msg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL & /*handled*/)
	{
		short zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
		float delta = zDelta / static_cast<float>(WHEEL_DELTA);
		Current.DeltaScroll += delta;
		return 0;
	}

	LRESULT Mouse::MouseButtonChange(UINT msg, WPARAM wParam, LPARAM /*lParam*/, BOOL & /*handled*/)
	{
		WORD button = 0;
		switch (msg)
		{
		case WM_RBUTTONDOWN:
			buttonsDown.push(MouseButton::MouseRight);
			Mouse::Current.SetButtonDown(MouseButton::MouseRight, true);
			break;
		case WM_MBUTTONDOWN:
			buttonsDown.push(MouseButton::MouseMiddle);
			Mouse::Current.SetButtonDown(MouseButton::MouseMiddle, true);
			break;
		case WM_LBUTTONDOWN:
			buttonsDown.push(MouseButton::MouseLeft);
			Mouse::Current.SetButtonDown(MouseButton::MouseLeft, true);
			break;
		case WM_XBUTTONDOWN:
			button = GET_XBUTTON_WPARAM(wParam);
			if (button == XBUTTON1)
			{
				buttonsDown.push(MouseButton::MouseX1);
				Mouse::Current.SetButtonDown(MouseButton::MouseX1, true);
			}
			else
			{
				buttonsDown.push(MouseButton::MouseX2);
				Mouse::Current.SetButtonDown(MouseButton::MouseX2, true);
			}
			break;
		case WM_RBUTTONUP:
			buttonsDown.push(MouseButton::MouseRight);
			Mouse::Current.SetButtonDown(MouseButton::MouseRight, false);
			break;
		case WM_MBUTTONUP:
			buttonsDown.push(MouseButton::MouseMiddle);
			Mouse::Current.SetButtonDown(MouseButton::MouseMiddle, false);
			break;
		case WM_LBUTTONUP:
			buttonsDown.push(MouseButton::MouseLeft);
			Mouse::Current.SetButtonDown(MouseButton::MouseLeft, false);
			break;
		case WM_XBUTTONUP:
			button = GET_XBUTTON_WPARAM(wParam);
			if (button == XBUTTON1)
			{
				buttonsUp.push(MouseButton::MouseX1);
				Mouse::Current.SetButtonDown(MouseButton::MouseX1, false);
			}
			else
			{
				buttonsUp.push(MouseButton::MouseX2);
				Mouse::Current.SetButtonDown(MouseButton::MouseX2, false);
			}
			break;
		}
		return LRESULT();
	}

	LRESULT Mouse::MouseMove(UINT /*msg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL & /*handled*/)
	{
		Current.ScreenXPos = GET_X_LPARAM(lParam);
		Current.ScreenYPos = GET_Y_LPARAM(lParam);

		return 0;
	}

	void Mouse::Update()
	{
		while (buttonsDown.size())
		{
			MouseButton button = buttonsDown.front();
			buttonsDown.pop();
			Globals::EventSystemInstance.Dispatch(new MouseButtonEvent(button, true));
		}
		while (buttonsUp.size())
		{
			MouseButton button = buttonsUp.front();
			buttonsUp.pop();
			Globals::EventSystemInstance.Dispatch(new MouseButtonEvent(button, false));
		}
	}

	void Mouse::PrepairForNextFrame()
	{
		Last = Current;
		Current.DeltaScroll = 0;
	}
}

