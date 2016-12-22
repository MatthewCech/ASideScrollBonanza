#include "KeyboardState.h"

namespace ASSB
{
	KeyboardState::KeyboardState() : KeysDown{ 0 }
	{
	}

	bool KeyboardState::IsKeyDown(Key key)
	{
		unsigned char k = static_cast<unsigned char>(key);
		return KeysDown[k];
	}

	void KeyboardState::SetKeyDown(Key key, bool down)
	{
		unsigned char k = static_cast<unsigned char>(key);
		KeysDown[k] = down;
	}

	bool KeyboardState::operator[](Key key)
	{
		unsigned char k = static_cast<unsigned char>(key);
		return KeysDown[k];
	}
}
