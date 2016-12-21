namespace OEvent
{
  // Connects to the event system and automatically stores the delegate ID.
  template <typename Caller, typename EventType>
  void ObjectEventManager::Connect(Caller *c, void(Caller::*func)(EventType *))
  {
    // Register and push the registered ID and push it to the back of the connections structure.
    connections_.push_back({ eventSystem_.Register(c, func) });
  }
}
