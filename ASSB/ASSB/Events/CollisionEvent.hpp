#pragma once
//#include "Globals.hpp"
#include "EventSystem/Event.hpp"


namespace ASSB
{
	// The last two objects that collided
	class CollisionEvent : public EventSystem::Event
	{
	public:
		typedef unsigned long long TmpCollID;
		CollisionEvent(TmpCollID id1, TmpCollID id2) : ID1(id1), ID2(id2) { }
		TmpCollID ID1;
		TmpCollID ID2;

	private:
		// Omit
		CollisionEvent(const CollisionEvent &rhs) = delete;
		CollisionEvent &operator=(const CollisionEvent &rhs) = delete;
	};
}
