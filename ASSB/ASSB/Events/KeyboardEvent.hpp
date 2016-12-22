#include "EventSystem\Event.hpp"
#include "Input/Key.h"



namespace ASSB
{
	// An event designed to signify user input.
	class KeyboardEvent : public EventSystem::Event
	{
	public:
		// Constructor
		KeyboardEvent(ASSB::Key key, bool down):  Key(key) , Down(down){ }

		// Variables
		ASSB::Key Key;
		bool Down;
	};
}
