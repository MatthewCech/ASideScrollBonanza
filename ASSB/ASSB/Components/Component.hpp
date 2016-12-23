#pragma once
#include "EventSystem\ObjectEventManager.hpp"
#include "Globals.hpp"



namespace ASSB
{
	// A base-class to allow us to standardize component contents when necessary.
	class Component : public EventSystem::ObjectEventManager
	{
	public:
		Globals::ObjectID Owner;
		// Constructor / Destructor
		Component(Globals::ObjectID owner);
		virtual ~Component();
	private:
		Component &operator=(const Component &rhs) = delete;
	};
}
