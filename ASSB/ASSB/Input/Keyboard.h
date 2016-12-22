#pragma once
#include "KeyboardState.h"
#include <queue>

//all this for one include @.@
#pragma warning(push, 0)
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN
#undef VC_EXTRALEAN
#pragma warning(pop)

namespace ASSB
{
	class GameEngine;

	class Keyboard
	{
		friend class GameEngine;
	public:
		/// <summary>
		/// the keyboard state for this game loop
		/// </summary>
		static KeyboardState Current;
		/// <summary>
		/// the keyboard state for the previous game loop
		/// </summary>
		static KeyboardState Last;

		/// <summary>
		/// gets if a key was pressed this frame, but not the last one
		/// </summary>
		/// <param name="key">the Keyboard key to check</param>
		bool WasKeyPressed(Key key);
		/// <summary>
		/// gets if a key is currently down
		/// </summary>
		/// <param name="key">the Keyboard key to check</param>
		bool IsKeyDown(Key key);
	private:
		static std::queue<Key> keysDown;
		static std::queue<Key> keysUp;

		static LRESULT KeyDown(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled);
		static LRESULT KeyUp(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled);
		static LRESULT SysKeyDown(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled);
		static LRESULT SysKeyUp(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled);
		static void Update();
		static void PrepairForNextFrame();
	};
}
