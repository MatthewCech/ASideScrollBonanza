#include "PlayerManagerComponent.hpp"
#include "Globals.hpp"
#include "FileSystem/ImagePreloadingMapper.hpp"
#include "GameEngine/GameEngine.h"
#include "Input/Key.h"
#include "Events/KeyboardEvent.hpp"
#include "Events/UpdateEvent.hpp"


namespace ASSB
{
	PlayerManagerComponent::PlayerManagerComponent(Globals::ObjectID owner)
		: Component(owner),
		active_(false)
	{
		// Connect events
		Connect(this, &PlayerManagerComponent::keyDownEvent);
		Connect(this, &PlayerManagerComponent::Update);
		Connect(this, &PlayerManagerComponent::Collide);
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

		//todo I need collision events before I can limit jumping
		if (e->Down)
		{
			if (k == Key::Space && CanJump)
			{
				IsJump = 0.15f;
				CanJump = false;
			}
		}
		else
		{
			if (k == Key::Space)
			{
				IsJump = 0;
			}
		}
	}

	void PlayerManagerComponent::Update(UpdateEvent * e)
	{
		if (!active_)
			return;
		float dt = static_cast<float>(e->Time.DT);
		ComponentHandle<RigidBodyComponent> rigidBody = GameEngine::Instance->GetComponent<RigidBodyComponent>(Owner);

		Graphics::Vector4 velocity = rigidBody->GetVelocity();
		velocity.Y -= 40 * dt;
		velocity.X = 5;

		if (IsJump > 0)
		{
			velocity.Y += 150 * dt;
			IsJump -= dt;
		}

		//fake drag
		velocity *= 0.96f;

		rigidBody->SetVelocity(velocity);


		//do the camera
		Graphics::Vector4 campos = GameEngine::Instance->Camera.GetPosition();
		Graphics::Vector4 pPos = GameEngine::Instance->GetComponent<TransformComponent>(Owner)->GetPosition();

		campos.X = pPos.X;

		float diff = pPos.Y - campos.Y;
		diff /= 20;

		campos.Y += diff;

		GameEngine::Instance->Camera.SetPosition(campos);
	}

	void PlayerManagerComponent::Collide(CollisionEvent * e)
	{
		if (!active_)
			return;

		if (e->ID1 != Owner && e->ID2 != Owner)
			return;

		Globals::ObjectID Other;
		if (e->ID1 == Owner)
			Other = e->ID2;
		else
			Other = e->ID1;

		CanJump = true;
	}
}
