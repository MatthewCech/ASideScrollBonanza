#pragma once
#include "EventSystem\Event.hpp"
#include "Input/MouseButton.h"



namespace ASSB
{
	// An event designed to signify user input.
	class MouseButtonEvent : public EventSystem::Event
	{
	public:
		// Constructor
		MouseButtonEvent(MouseButton button, bool down) : Button(button), Down(down) { }

		// Variables
		MouseButton Button;
		bool Down;
	};
}