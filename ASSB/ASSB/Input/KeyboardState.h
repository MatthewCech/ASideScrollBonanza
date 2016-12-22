#pragma once
#include "Key.h"

namespace ASSB
{
	struct KeyboardState
	{
		KeyboardState();

		bool IsKeyDown(Key key);
		void SetKeyDown(Key key, bool down);

		bool operator[](Key key);
	private:
		bool KeysDown[256];
	};
}
