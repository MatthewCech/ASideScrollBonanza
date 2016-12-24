#include "MenuComponent.hpp"
#include "GameEngine/GameEngine.h"
#include "SpriteComponent.hpp"
#include "FileSystem/ImagePreloadingMapper.hpp"
#include "Events/UIChangeEvent.hpp"
#include "Events/UISelectEvent.hpp"
#include "GameEngine/Utilities.hpp"



namespace ASSB
{
	// Constructor
	MenuComponent::MenuComponent(Globals::ObjectID owner, std::string indicatorTag, bool vertical)
		: Component(owner)
		, active_(true)
		, selected_(0)
		, spacing_({ 0, -1, 0 })
		, pos_({ 0, 0, .05f })
		, selectionIndicator_()
		, interactables_()
		, vertical_(vertical)
	{
		selectionIndicator_ = GameEngine::Instance->CreateGameObject();
		SetIndicatorTag(indicatorTag, { 1,1,0 });

		// Connect Events
		Connect(this, &MenuComponent::handleKeyboardEvent);
	}

	void MenuComponent::SetVisible(bool isVisible)
	{
		if (isVisible == false)
		{
			for (size_t i = 0; i < interactables_.size(); ++i)
			{
				GameEngine::Instance->GetComponent<SpriteComponent>(interactables_[i].first)
					->Visible = false;
			}
			GameEngine::Instance->GetComponent<SpriteComponent>(selectionIndicator_)->Visible = false;
		}
		else
		{
			for (size_t i = 0; i < interactables_.size(); ++i)
			{
				GameEngine::Instance->GetComponent<SpriteComponent>(interactables_[i].first)
					->Visible = true;
			}
			GameEngine::Instance->GetComponent<SpriteComponent>(selectionIndicator_)->Visible = true;
		}
	}

	void MenuComponent::SetActive(bool isActive)
	{
		active_ = isActive;
	}

	bool MenuComponent::IsActive()
	{
		return active_;
	}
	// 0-based indexing into the array
	void MenuComponent::SetIndicated(int index)
	{
		if (index < 0)
			index = 0;
		if (index > static_cast<int>(interactables_.size()) - 1)
			index = static_cast<int>(interactables_.size()) - 1;
		
		selected_ = index;
	}


	// Selects the current index, dispatching the associated event.
	void MenuComponent::Select()
	{
		Globals::EventSystemInstance.Dispatch(new UISelectEvent());
		interactables_[static_cast<size_t>(selected_)].second->Dispatch();
	}


	// Keyboard event callback
	void MenuComponent::handleKeyboardEvent(KeyboardEvent *e)
	{
		if (active_)
		{
			if(e->Down)
			{
				const Key k{ e->Key };
				if (vertical_)
				{
					if (k == Key::S || k == Key::Down || k == Key::Numpad_2)
						IncrementIndicated();
					else if (k == Key::W || k == Key::Up || k == Key::Numpad_8)
						DectementIndicated();
				}
				else // Horizontal
				{
					if (k == Key::D || k == Key::Right || k == Key::Numpad_6)
						IncrementIndicated();
					else if (k == Key::A || k == Key::Left || k == Key::Numpad_4)
						DectementIndicated();
				}

				// Key selected
				if (k == Key::Enter || k == Key::Space || k == Key::Numpad_Enter)
					Select();
			}
		}
	}


	// Updates location of selection indicator to position of the new item
	void MenuComponent::updateSelectionIndicator()
	{
		if (interactables_.size() == 0)
			return;

		ComponentHandle<TransformComponent> indicatorLoc = GameEngine::Instance->GetComponent<TransformComponent>(selectionIndicator_);
		ComponentHandle<TransformComponent> interactableLoc = GameEngine::Instance->GetComponent<TransformComponent>(interactables_[static_cast<size_t>(selected_)].first);
		//!TODO: ACTIONS SYSTEM FOR INTERPOLATION
		Utilities::Instance->InterpolatePos(selectionIndicator_, interactableLoc->GetPosition() - Graphics::Vector4(0, 0, .01f), 80);
		//indicatorLoc->SetPosition(interactableLoc->GetPosition());
	}


	// Increments the position: Goes Down or Right
	void MenuComponent::IncrementIndicated()
	{
		++selected_;
		if (selected_ >= static_cast<int>(interactables_.size()))
		  selected_ = 0;

		Globals::EventSystemInstance.Dispatch(new UIChangeEvent());
		updateSelectionIndicator();
	}


	// Decrements the positon: Goes Up or Left.
	void MenuComponent::DectementIndicated()
	{
		--selected_;
		if (selected_ < 0)
			selected_ = static_cast<int>(interactables_.size()) - 1;

		Globals::EventSystemInstance.Dispatch(new UIChangeEvent());
		updateSelectionIndicator();
	}


	// Updates the selection location
	void MenuComponent::updateSpacing()
	{
		for (size_t i = 0; i < interactables_.size(); ++i)
		{
			GameEngine::Instance->GetComponent<TransformComponent>(interactables_[i].first)->
				SetPosition(pos_ + spacing_ * static_cast<float>(i));
		}
		if (interactables_.size() > 0)
			updateSelectionIndicator();
	}

	// Getters and Setters
	void MenuComponent::SetIndicatorTag(std::string indicatorTag, Graphics::Vector4 scale)
	{
		if (indicatorTag.size() > 0)
		{
			std::string path = FileSystem::ImagePreloadingMapper::Retrieve(indicatorTag);
			if (path.size() > 0)
			{
				GameEngine::Instance->GetComponent<SpriteComponent>(selectionIndicator_)->
					AddPath(std::wstring(path.begin(), path.end()));
				GameEngine::Instance->GetComponent<TransformComponent>(selectionIndicator_)->
					SetScale(scale.X, scale.Y);
				updateSelectionIndicator();
			}
		}
	}
	void MenuComponent::SetVertical(bool isVertical)
	{
		vertical_ = isVertical;
	}
	bool MenuComponent::IsVertical()
	{
		return vertical_;
	}
	void MenuComponent::SetSpacing(Graphics::Vector4 spacingVal)
	{
		spacing_ = spacingVal;
	}
	void MenuComponent::SetPosition(Graphics::Vector4 newPos)
	{
		pos_.X = newPos.X;
		pos_.Y = newPos.Y;
		pos_.Z = 0.5f;
		updateSpacing();
	}
	Graphics::Vector4 MenuComponent::GetPosition()
	{
		return pos_;
	}
	int MenuComponent::GetIndicated()
	{
		return selected_;
	}
	Graphics::Vector4 MenuComponent::GetSpacing()
	{
		return spacing_;
	}
}