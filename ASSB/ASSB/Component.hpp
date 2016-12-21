#pragma once
#include "EventSystem\ObjectEventManager.hpp"



namespace ASSB
{
	// A base-class to allow us to standardize component contents when necessary.
	class Component : public EventSystem::ObjectEventManager
	{
	public:
		// Constructor / Destructor
		Component();
		virtual ~Component();
	private:
		Component &operator=(const Component &rhs) = delete;
	};
}
