#include "PlayerManagerComponent.hpp"
#include "Globals.hpp"
#include "FileSystem/ImagePreloadingMapper.hpp"
#include "GameEngine/GameEngine.h"
#include "Input/Key.h"
#include "Events/KeyboardEvent.hpp"


namespace ASSB
{
	PlayerManagerComponent::PlayerManagerComponent()
		: active_(false)
	{
		// Connect events
		Connect(this, &PlayerManagerComponent::keyDownEvent);
	}


	// Set player image (utility function, consider moving)
	void PlayerManagerComponent::SetImage(std::string imageTag, Graphics::Vector4 scale)
	{
		Globals::ObjectID id = GameEngine::Instance->GetIdOf("player");
		if (imageTag.size() > 0)
		{
			std::string path = FileSystem::ImagePreloadingMapper::Retrieve(imageTag);
			if (path.size() > 0)
			{
				GameEngine::Instance->GetComponent<SpriteComponent>(id)->
					Path = std::wstring(path.begin(), path.end());
				GameEngine::Instance->GetComponent<TransformComponent>(id)->
					SetScale(scale.X, scale.Y);
			}
		}
	}

	
	// Get/set
	bool PlayerManagerComponent::IsActive()
	{
		return active_;
	}
	void PlayerManagerComponent::SetActive(bool isActive)
	{
		active_ = isActive;
	}


	  ///////////////////
	 // Event related //
	///////////////////
	void PlayerManagerComponent::keyDownEvent(KeyboardEvent *e)
	{
		if (!active_)
			return;
		Globals::ObjectID id = GameEngine::Instance->GetIdOf("player");
		ComponentHandle<RigidBodyComponent> rigidBody = GameEngine::Instance->GetComponent<RigidBodyComponent>(id);

		// Handle position movement
		const ASSB::Key k{ e->Key };
		float accelSpeed = .1f;
		if (k == Key::A || k == Key::Left)
			rigidBody->SetVelocity(rigidBody->GetVelocity() + Graphics::Vector4(-accelSpeed, 0, 0));
		else if (k == Key::S || k == Key::Down)
			rigidBody->SetVelocity(rigidBody->GetVelocity() + Graphics::Vector4(0, -accelSpeed, 0));
		else if (k == Key::D || k == Key::Right)
			rigidBody->SetVelocity(rigidBody->GetVelocity() + Graphics::Vector4(accelSpeed, 0, 0));
		else if (k == Key::W || k == Key::Up)
			rigidBody->SetVelocity(rigidBody->GetVelocity() + Graphics::Vector4(0, accelSpeed, 0));

	}
}
