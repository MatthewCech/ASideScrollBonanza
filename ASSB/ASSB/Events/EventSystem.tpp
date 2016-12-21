#include "DelegateMemberFunction.hpp"
#include "DelegateGlobalFunction.hpp"



namespace OEvent
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
