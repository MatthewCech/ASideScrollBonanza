#include "PlayerManagerComponent.hpp"
#include "Globals.hpp"
#include "FileSystem/ImagePreloadingMapper.hpp"
#include "GameEngine/GameEngine.h"
#include "Input/Key.h"
#include "Events/KeyboardEvent.hpp"
#include "Events/UpdateEvent.hpp"
#include "Events/SwitchEvent.hpp"
#include "Events/LoseEvent.hpp"


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

		JumpVel = 150;
	}


	// Set player image (utility function, consider moving)
	void PlayerManagerComponent::SetImage(std::string imageTagLight, std::string imageTagDark, Graphics::Vector4 scale)
	{
		Globals::ObjectID id = GameEngine::Instance->GetIdOf("player");
		if (imageTagLight.size() > 0)
			if(imageTagDark.size() > 0)
			{
				// Set assets
				std::string pathLight = FileSystem::ImagePreloadingMapper::Retrieve(imageTagLight);
				std::string pathDark = FileSystem::ImagePreloadingMapper::Retrieve(imageTagDark);
				ComponentHandle<SpriteComponent> sprite = GameEngine::Instance->GetComponent<SpriteComponent>(id);
				
				// These are "backwards" because player light is world dark
				sprite->AddAltPath(std::wstring(pathLight.begin(), pathLight.end()));
				sprite->AddPath(std::wstring(pathDark.begin(), pathDark.end()));
				sprite->SetSwappable(true);

				// Set scale
				GameEngine::Instance->GetComponent<TransformComponent>(id)->
					SetScale(scale.X, scale.Y);
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

		if (e->Down)
		{
			if (k == Key::Space && CanJump)
			{
				IsJump = 0.15f;
				CanJump = false;
			}
			else if (k == Key::Tab)
			{
				auto transform = GameEngine::Instance->GetComponent<TransformComponent>(Owner);
				if (White)
				{//make black
					transform->SetScale(0.5, 1);
					JumpVel = 150;
				}
				else
				{//make white
					transform->SetScale(0.25, 0.5);
					JumpVel = 110;
				}
				White = !White;
				Globals::EventSystemInstance.Dispatch(new SwitchEvent(White));
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
			velocity.Y += JumpVel * dt;
			IsJump -= dt;
		}

		//fake drag
		velocity *= 0.96f;

		rigidBody->SetVelocity(velocity);


		//do the camera
		Graphics::Vector4 campos = GameEngine::Instance->Camera.GetPosition();
		Graphics::Vector4 pPos = GameEngine::Instance->GetComponent<TransformComponent>(Owner)->GetPosition();

		campos.X = pPos.X + 2.0f;

		float diff = pPos.Y - campos.Y + .75f;
		diff /= 20;

		campos.Y += diff;

		//!TODO:BETTER ALTERNATIVE? Currently, Force player location above 0;
		ComponentHandle<TransformComponent> tComp = GameEngine::Instance->GetComponent<TransformComponent>(Owner);
		if (tComp->GetPosition().Y < (.5 + .2f))
		{
			Graphics::Vector4 toFix = tComp->GetPosition();
			Graphics::Vector4 velToFix = rigidBody->GetVelocity();
			toFix.Y = .75f;
			velToFix.Y = 0;
			rigidBody->SetVelocity(velToFix);
			tComp->SetPosition(toFix);
		}

		GameEngine::Instance->Camera.SetPosition(campos);
	}

	void PlayerManagerComponent::Collide(CollisionEvent * e)
	{
		if (e->ID1 != Owner && e->ID2 != Owner)
			return;

		Globals::ObjectID Other;
		if (e->ID1 == Owner)
			Other = e->ID2;
		else
			Other = e->ID1;

		if (GameEngine::Instance->GetNameOf(Other) == "PK")
			Globals::EventSystemInstance.Dispatch(new LoseEvent(GameEngine::Instance->Time));

		CanJump = true;
	}
}
