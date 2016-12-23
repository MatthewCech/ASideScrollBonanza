#pragma once
#include "Globals.hpp"


namespace EventSystem
{
	// Base class to allow holding of the templatized EventCarrier class
	// for dispatching of events at a later time.
	class ECBase
	{
	public:
		virtual void Dispatch() { }
	};

	// Templatized Management class for dealing with
	// dispatching at a later time than they are passed to you.
	template <typename EventType>
	class EventCarrier : public ECBase
	{
	public:
		void Dispatch()
		{
			ASSB::Globals::EventSystemInstance.Dispatch<EventType>(ToDispatch);
		}
		EventType *ToDispatch;
	};
}
