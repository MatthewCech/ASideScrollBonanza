namespace EventSystem
{
  // Connects to the event system and automatically stores the delegate ID.
  template <typename Caller, typename EventType>
  void ObjectEventManager::Connect(Caller *c, void(Caller::*func)(EventType *))
  {
    // Register and push the registered ID and push it to the back of the connections structure.
    connections_.push_back({ eventSystem_.Register(c, func) });
  }


	// Allows the user to register "vaguely", meaning no automatic casting will occur
	// past your guarentee of an event object being passed. If used, it will have
	// to be reinterpret cast to the correct object.
	template <typename Caller, typename EventToBind>
	void ObjectEventManager::ConnectVague(Caller *c, void(Caller::*func)(Event *))
	{
		// Register and push the registered ID and push it to the back of the connections structure.
		connections_.push_back({ eventSystem_.RegisterVague<Caller, EventToBind>(c, func) });
	}
}
