#include "EventSystem.hpp"



namespace OEvent
{
  // Constructor
  EventSystem::EventSystem()
    : systemMap_()
    , automaticCleanup_(true)
  {  }


  // Destructor
  EventSystem::~EventSystem()
  {  }


  // Disconnects the specified O_ID from the event system.
  void EventSystem::Disconnect(O_ID toDisconnect)
  {
    for (auto& iter : systemMap_)
      iter.second.Remove(toDisconnect);
  }


  // Performs an update on the event system, cleaning up events 
  // that have been marked as no longer necessary.
  void EventSystem::Upkeep()
  {
    for (auto& iter : systemMap_)
      iter.second.CleanRemoved();
  }
}