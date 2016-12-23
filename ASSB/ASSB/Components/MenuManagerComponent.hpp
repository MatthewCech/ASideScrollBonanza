#pragma once
#include "Component.hpp"
#include "Globals.hpp"
#include <vector>
#include <string>
#include <utility>
#include <memory>
#include "EventSystem/Event.hpp"
#include "EventSystem/EventCarrier.hpp"
#include "Events/KeyboardEvent.hpp"
#include "Graphics/Vector4.h"



namespace ASSB
{
	// MenuManagerComponent allows creation and management of a few other objects that allow for interfacing.
	class MenuManagerComponent : public Component
	{
	public:
		// Constructor
		MenuManagerComponent(std::string indicatorTag = "", bool vertical_ = true);

		// Templatized Function
		template<typename EventType>
		void AddInteractable(std::string tag, Graphics::Vector4 scale, EventType *event);

		// Public member functions
		void IncrementIndicated();
		void DectementIndicated();
		void Select();

		void SetIndicatorTag(std::string indicator, Graphics::Vector4 scale);
		void SetVertical(bool isVertical);
		bool IsVertical();
		void SetIndicated(int index);
		void SetSpacing(Graphics::Vector4 spacing);
		void SetPosition(Graphics::Vector4 newPos);
		Graphics::Vector4 GetPosition();
		int GetIndicated();
		Graphics::Vector4 GetSpacing();

	private:
		// Variables
		bool active_;
		int selected_;
		Graphics::Vector4 spacing_;
		Graphics::Vector4 pos_;
		Globals::ObjectID selectionIndicator_;
		bool vertical_;
		std::vector < std::pair<Globals::ObjectID, EventSystem::ECBase *>> interactables_;

		// Private member functions
		void handleKeyboardEvent(KeyboardEvent *e);
		void updateSelectionIndicator();
		void updateSpacing();

		// Omit
		MenuManagerComponent *operator=(const MenuManagerComponent &rhs) = delete;
		//MenuManagerComponent(const MenuManagerComponent &rhs) = delete;
	};
}

#include "MenuManagerComponent.tpp"
