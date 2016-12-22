#include "EventSystem\Event.hpp"



namespace ASSB
{
	// What type of input this event is representing
	enum InputType { KEYBOARD, SOMETHING_ELSE };

	// An event designed to signify user input.
	class InputEvent : public EventSystem::Event
	{
	public:
		// Constructor
		InputEvent(char value, InputType type = KEYBOARD): Value(value), Type(type) { }

		// Variables
		char Value;
		InputType Type;
	};
}
