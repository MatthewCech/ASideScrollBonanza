namespace ASSB
{
	template<typename EventType>
	void MenuComponent::AddInteractable(std::string tag, Graphics::Vector4 scale, EventType *evt)
	{
		// Object instance
		Globals::ObjectID id = GameEngine::Instance->CreateGameObject();
		std::string path = FileSystem::ImagePreloadingMapper::Retrieve(tag);
		if (path.size() > 0)
		{
			GameEngine::Instance->GetComponent<SpriteComponent>(id)->
				Path = std::wstring(path.begin(), path.end());
		}
		ComponentHandle<TransformComponent> transform = GameEngine::Instance->GetComponent<TransformComponent>(id);
		transform->SetPosition(pos_ + spacing_ * static_cast<float>(interactables_.size()));
		transform->SetScale(scale.X, scale.Y);
		
		// Event to dispatch later
		EventSystem::EventCarrier<EventType> *ec = new EventSystem::EventCarrier<EventType>();
		ec->ToDispatch = evt;
		EventSystem::ECBase *ecb = dynamic_cast<EventSystem::ECBase *>(ec);

		// Add our lovely new pair.
		interactables_.push_back({ id, ecb });
		updateSelectionIndicator();
	}
}
