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
#include "FileSystem/ImagePreloadingMapper.hpp"



namespace ASSB
{
	// MenuComponent allows creation and management of a few other objects that allow for interfacing.
	class MenuComponent : public Component
	{
	public:
		// Constructor
		MenuComponent(std::string indicatorTag = "", bool vertical_ = true);

		// Templatized Function
		template<typename EventType>
		void AddInteractable(std::string tag, Graphics::Vector4 scale, EventType *event);

		// Public member functions
		void IncrementIndicated();
		void DectementIndicated();
		void Select();

		// Setters
		void SetIndicatorTag(std::string indicator, Graphics::Vector4 scale);
		void SetSpacing(Graphics::Vector4 spacing);
		void SetPosition(Graphics::Vector4 newPos);
		void SetVertical(bool isVertical);
		void SetIndicated(int index);
		void SetActive(bool isActive);
		void SetVisible(bool isVisible);

		// Getters
		Graphics::Vector4 GetPosition();
		Graphics::Vector4 GetSpacing();
		int GetIndicated();
		bool IsVertical();
		bool IsActive();

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
		MenuComponent *operator=(const MenuComponent &rhs) = delete;
		//MenuComponent(const MenuComponent &rhs) = delete;
	};
}

#include "MenuComponent.tpp"
