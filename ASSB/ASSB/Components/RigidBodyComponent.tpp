namespace ASSB
{
	template<typename EventType>
	void RigidBodyComponent::AddDispatchOnCollision(EventType *evt)
	{
		EventSystem::EventCarrier<EventType> *ec = new EventSystem::EventCarrier<EventType>();
		ec->ToDispatch = evt;
		EventSystem::ECBase *ecb = dynamic_cast<EventSystem::ECBase *>(ec);
		dispatchables_.push_back(ecb);
	}
}

