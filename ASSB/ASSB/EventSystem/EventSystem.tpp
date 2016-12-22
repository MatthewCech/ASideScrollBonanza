#include "DelegateMemberFunction.hpp"
#include "DelegateGlobalFunction.hpp"



namespace EventSystem
{
  // Register for a member function event.
  // Caller is implicit when registering.
  // Event type is implicit when registering.
  template <typename Caller, typename EventType>
  O_ID EventSystem::Register(Caller *c, void(Caller::*func)(EventType *))
  {
    DelegateMemberFunction<Caller, EventType> *dmf = new DelegateMemberFunction<Caller, EventType>(func, c);
    return systemMap_[typeid(EventType)].Add(dmf);
  }


	// Vague event registration- allows for an event to be associated with 
	// any form of function so long as it takes an event *. It will have to
	// be recast by the user to whatever type they want later.
	template <typename Caller, typename EventType>
	O_ID EventSystem::RegisterVague(Caller *c, void(Caller::*func)(Event *))
	{
	  DelegateMemberFunction<Caller, Event> *dmf = new DelegateMemberFunction<Caller, Event>(func, c);
	  return systemMap_[typeid(EventType)].Add(dmf);
	}


  // Register for global event
  // Event Type is implicit when registering.
  template <typename EventType>
  O_ID EventSystem::Register(void(*func)(EventType *e))
  {
    DelegateGlobalFunction<EventSystem> *dgf = new DelegateGlobalFunction<EventSystem>(e);
    return systemMap_[typeid(EventType)].Add(dgf);
  }


  // Dispatches an event.
  // Event type is inferred based on the argument.
  template <typename EventType>
  int EventSystem::Dispatch(EventType *e)
  {
    int toRet{ systemMap_[typeid(EventType)].Dispatch(e) };

    if(automaticCleanup_)
      delete e;

    return toRet;
  }
}
