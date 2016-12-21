#include "Component.hpp"
#include "Globals.hpp"



namespace ASSB
{
	// Constructor
	Component::Component() : ObjectEventManager(Globals::EventSystemInstance)
	{  }


	// Virtual Destructor - still requires implementation
	Component::~Component()
	{  }
}
