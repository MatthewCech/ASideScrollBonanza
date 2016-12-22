namespace ASSB
{
	// Play when the following event type shows up
	template <typename EventType>
	void SoundEmitterComponent::PlayOnEvent()
	{
		Connect<EventType>(this, eventCallback);
	}
}
