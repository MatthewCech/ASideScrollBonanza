#pragma once
#include <typeindex>
#include <map>
#include "DelegateGroup.hpp"



namespace EventSystem
{
  class EventSystem
  {
  public:
    // Constructor
    EventSystem();
    ~EventSystem();
    
    // Member function delegate
    template <typename Caller, typename EventType>
    O_ID Register(Caller *c, void(Caller::*func)(EventType *));

		// Vague member function delegate
		template <typename Caller, typename EventType>
		O_ID RegisterVague(Caller *c, void(Caller::*func)(Event *));

    // Global function delegate 
    template <typename EventType>  
    O_ID Register(void(*func)(EventType *e));

    // Event dispatching
    template <typename EventType>
    int Dispatch(EventType *e, bool cleanup = true);

    // Event disconnecting
    void Disconnect(O_ID toDisconnect);
    void Upkeep();

  private:
    // Variables
    std::map< std::type_index, DelegateGroup > systemMap_;
    bool automaticCleanup_;
  };
}

#include "EventSystem.tpp"
