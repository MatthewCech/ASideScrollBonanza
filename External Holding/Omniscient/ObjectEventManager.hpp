#pragma once
#include <vector>
#include "ODefines.hpp"
#include "EventSystem.hpp"


namespace OEvent
{
  // Handles connecting and disconnecting of events based on their IDs.
  // This service is provided for objects only, and is not something that 
  // is provided for global functions that are part of the event system.
  class ObjectEventManager
  {
  public:
    // Constructor and Destructor
    ObjectEventManager(EventSystem &es);
    virtual ~ObjectEventManager();

    // Member Functions
    template <typename Caller, typename EventType>
    void Connect(Caller *c, void(Caller::*func)(EventType *));
    //void Disconnect(O_ID toDisconnect);

  private:
    // Variables
    std::vector<O_ID> connections_;
    EventSystem &eventSystem_;
  };
}

#include "ObjectEventManager.tpp"
