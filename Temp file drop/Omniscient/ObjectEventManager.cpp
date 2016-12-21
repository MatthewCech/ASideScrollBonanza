#include "ObjectEventManager.hpp"



namespace OEvent
{
  // Constructor takes the event system to manage the connection to as an argument.
  ObjectEventManager::ObjectEventManager(EventSystem &es)
    : connections_()
    , eventSystem_(es)
  {  }


  // Destructor - Disconnects all existing events from the event system.
  ObjectEventManager::~ObjectEventManager()
  {  
    for (unsigned int i{ 0 }; i < connections_.size(); ++i)
      eventSystem_.Disconnect(connections_[i]);
  }


  // Disconnects the specified O_ID from the event system and removes it from tracking
  // in the ObjectEventManager object.
  /*
  void ObjectEventManager::Disconnect(O_ID toDisconnect)
  {
    for (unsigned int i{ 0 }; i < connections_.size(); ++i)
      // ...
  }
  //*/
}

