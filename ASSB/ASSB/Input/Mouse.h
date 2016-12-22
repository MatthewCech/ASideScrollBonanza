#pragma once
#include "MouseState.h"
#include <queue>

//all this for one include @.@
#pragma warning(push, 0)
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#include <windowsx.h>
#undef WIN32_LEAN_AND_MEAN
#undef VC_EXTRALEAN
#pragma warning(pop)

namespace ASSB
{
	class GameEngine;

	class Mouse
	{
		friend class GameEngine;
	public:
		/// <summary>
		/// the mouse state for this game loop
		/// </summary>
		static MouseState Current;
		/// <summary>
		/// the mouse state for the previous game loop
		/// </summary>
		static MouseState Last;

		/// <summary>
		/// gets if a button is currently down
		/// </summary>
		/// <param name="key">the mouse button to check</param>
		static bool IsButtonDown(MouseButton button);
		
		/// <summary>
		/// gets if a button was pressed this frame, but not the last one
		/// </summary>
		/// <param name="key">the mouse button to check</param>
		static bool WasButtonPressed(MouseButton button);

	private:
		static std::queue<MouseButton> buttonsDown;
		static std::queue<MouseButton> buttonsUp;

		static LRESULT Scroll(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled);
		static LRESULT MouseButtonChange(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled);
		static LRESULT MouseMove(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled);
		static void Update();
		static void PrepairForNextFrame();
	};
}