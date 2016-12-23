#pragma once
#include "Component.hpp"
#include "Globals.hpp"
#include "Graphics/Vector4.h"


namespace ASSB
{
	// Handles player related events like movement and whatnot.
	class KeyboardEvent;
	class PlayerManagerComponent : public Component
	{
	public:
		// Constructor
		PlayerManagerComponent();

		// Member Functions
		bool IsActive();
		void SetImage(std::string tag, Graphics::Vector4 scale);
		void SetActive(bool isActive);

	private:
		// Variables
		bool active_; // Do we honor input and whatnot? (auto set to false when paused)

		// private member functions
		void keyDownEvent(KeyboardEvent *e);

		// Omit
		PlayerManagerComponent(const PlayerManagerComponent &rhs) = delete;
		PlayerManagerComponent &operator=(const PlayerManagerComponent &rhs) = delete;
	};
}
