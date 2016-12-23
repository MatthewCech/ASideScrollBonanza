#include "Component.hpp"
#include "Globals.hpp"



namespace ASSB
{
	// Constructor
	Component::Component(Globals::ObjectID owner) : ObjectEventManager(Globals::EventSystemInstance), Owner(owner)
	{  }


	// Virtual Destructor - still requires implementation
	Component::~Component()
	{  }
}
