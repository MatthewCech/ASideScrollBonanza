#include "Keyboard.h"

#include <iostream>
#include <iomanip>

#include "Globals.hpp"
#include "Events/KeyboardEvent.hpp"

namespace ASSB
{
	KeyboardState Keyboard::Current;
	KeyboardState Keyboard::Last;
	std::queue<Key> Keyboard::keysDown;
	std::queue<Key> Keyboard::keysUp;

	void Keyboard::PrepairForNextFrame()
	{
		Last = Current;
	}

	bool Keyboard::WasKeyPressed(Key key)
	{
		return Current[key] && !Last[key];
	}

	bool Keyboard::IsKeyDown(Key key)
	{
		return Current.IsKeyDown(key);
	}

	static Key processKey(WPARAM wParam, LPARAM lParam)
	{
		bool rightkey = (lParam & 0x01000000) != 0;//gets the "extended" info

		Key key;
		switch (wParam)
		{
		case VK_SHIFT:
			key = rightkey ? Key::RShift : Key::LShift;
			break;
		case VK_CONTROL:
			key = rightkey ? Key::RControl : Key::LControl;
			break;
		case VK_MENU:
			key = rightkey ? Key::RAlt : Key::LAlt;
			break;
		case VK_RETURN:
			key = rightkey ? Key::Numpad_Enter : Key::Enter;
			break;
		case VK_PAUSE:
			key = Key::Break;
			break;
		default:
			key = static_cast<Key>(wParam);
			break;
		}
		return key;
	}

	LRESULT Keyboard::KeyDown(UINT /*msg*/, WPARAM wParam, LPARAM lParam, BOOL & /*handled*/)
	{
		//get the key pressed
		Key key = processKey(wParam, lParam);

		//is that key down already?
		if (Current[key])
			return 0;

		Current.SetKeyDown(key, true);

		keysDown.push(key);

		return 0;
	}

	LRESULT Keyboard::KeyUp(UINT /*msg*/, WPARAM wParam, LPARAM lParam, BOOL & /*handled*/)
	{
		//get the key pressed
		Key key = processKey(wParam, lParam);

		//is that key up already?
		if (!Current[key])
			return 0;

		Current.SetKeyDown(key, false);

		keysUp.push(key);

		return 0;
	}

	LRESULT Keyboard::SysKeyDown(UINT /*msg*/, WPARAM wParam, LPARAM lParam, BOOL & /*handled*/)
	{
		//get the key pressed
		Key key = processKey(wParam, lParam);

		//is that key down already?
		if (Current[key])
			return 0;

		Current.SetKeyDown(key, true);

		keysDown.push(key);

		return 0;
	}

	LRESULT Keyboard::SysKeyUp(UINT /*msg*/, WPARAM wParam, LPARAM lParam, BOOL & /*handled*/)
	{
		//get the key pressed
		Key key = processKey(wParam, lParam);

		//is that key up already?
		if (!Current[key])
			return 0;

		Current.SetKeyDown(key, false);

		keysUp.push(key);

		return 0;
	}

	void Keyboard::Update()
	{
		while (keysDown.size())
		{
			Key key = keysDown.front();
			keysDown.pop();
			Globals::EventSystemInstance.Dispatch(new KeyboardEvent(key, true));
		}
		while (keysUp.size())
		{
			Key key = keysUp.front();
			keysUp.pop();
			Globals::EventSystemInstance.Dispatch(new KeyboardEvent(key, false));
		}
	}
}
