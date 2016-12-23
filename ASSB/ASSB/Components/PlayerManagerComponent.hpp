#pragma once
#include "Component.hpp"
#include "Globals.hpp"
#include "Graphics/Vector4.h"
#include "GameEngine/ComponentHandle.h"
#include "RigidBodyComponent.hpp"
#include "Events/CollisionEvent.hpp"


namespace ASSB
{
	// Handles player related events like movement and whatnot.
	class KeyboardEvent;
	class UpdateEvent;

	class PlayerManagerComponent : public Component
	{
	public:
		// Constructor
		PlayerManagerComponent(Globals::ObjectID owner);

		// Member Functions
		bool IsActive();
		void SetImage(std::string tag, Graphics::Vector4 scale);
		void SetActive(bool isActive);

	private:
		// Variables
		bool active_; // Do we honor input and whatnot? (auto set to false when paused)
		bool CanJump;
		float IsJump;

		// private member functions
		void keyDownEvent(KeyboardEvent *e);
		void Update(UpdateEvent *e);
		void Collide(CollisionEvent* e);

		// Omit
		PlayerManagerComponent(const PlayerManagerComponent &rhs) = delete;
		PlayerManagerComponent &operator=(const PlayerManagerComponent &rhs) = delete;
	};
}
