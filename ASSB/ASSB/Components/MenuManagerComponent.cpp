#include "MenuManagerComponent.hpp"
#include "GameEngine/GameEngine.h"
#include "SpriteComponent.hpp"
#include "FileSystem/ImagePreloadingMapper.hpp"



namespace ASSB
{
	// Constructor
	MenuManagerComponent::MenuManagerComponent(std::string indicatorTag, bool vertical)
		: active_(true)
		, selected_(0)
		, spacing_({ 0, 1, 0 })
		, pos_({ 0, 0, 0 })
		, selectionIndicator_()
		, interactables_()
		, vertical_(vertical)
	{
		selectionIndicator_ = GameEngine::Instance->CreateGameObject("MenuSelectionIndicator");
		SetIndicatorTag(indicatorTag);
	}


	// 0-based indexing into the array
	void MenuManagerComponent::SetIndicated(int index)
	{
		if (index < 0)
			index = 0;
		if (index > static_cast<int>(interactables_.size()) - 1)
			index = static_cast<int>(interactables_.size()) - 1;
		
		selected_ = index;
	}


	// Selects the current index, dispatching the associated event.
	void MenuManagerComponent::Select()
	{
		interactables_[static_cast<size_t>(selected_)].second->Dispatch();
	}


	// Keyboard event callback
	void MenuManagerComponent::handleKeyboardEvent(KeyboardEvent *e)
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
			}
		}
	}


	// Updates location of selection indicator to position of the new item
	void MenuManagerComponent::updateSelectionIndicator()
	{
		ComponentHandle<TransformComponent> indicatorLoc = GameEngine::Instance->GetComponent<TransformComponent>(selectionIndicator_);
		ComponentHandle<TransformComponent> interactableLoc = GameEngine::Instance->GetComponent<TransformComponent>(interactables_[static_cast<size_t>(selected_)].first);
		//!TODO: ACTIONS SYSTEM FOR INTERPOLATION
		indicatorLoc->SetPosition(interactableLoc->GetPosition());
	}


	// Increments the position: Goes Down or Right
	void MenuManagerComponent::IncrementIndicated()
	{
		++selected_;
		if (selected_ >= static_cast<int>(interactables_.size()))
		  selected_ = 0;

		updateSelectionIndicator();
	}


	// Decrements the positon: Goes Up or Left.
	void MenuManagerComponent::DectementIndicated()
	{
		--selected_;
		if (selected_ < 0)
			selected_ = static_cast<int>(interactables_.size());

		updateSelectionIndicator();
	}


	void MenuManagerComponent::updateSpacing()
	{
		for (size_t i = 0; i < interactables_.size(); ++i)
		{
			GameEngine::Instance->GetComponent<TransformComponent>(interactables_[i].first)->
				SetPosition(pos_ + spacing_ * static_cast<float>(i));
		}
	}

	// Getters and Setters
	void MenuManagerComponent::SetIndicatorTag(std::string indicatorTag)
	{
		if (indicatorTag.size() > 0)
		{
			std::string path = FileSystem::ImagePreloadingMapper::Retrieve(indicatorTag);
			if (path.size() > 0)
			{
				GameEngine::Instance->GetComponent<SpriteComponent>(selectionIndicator_)->
					Path = std::wstring(path.begin(), path.end());
			}
		}
	}
	void MenuManagerComponent::SetVertical(bool isVertical)
	{
		vertical_ = isVertical;
	}
	bool MenuManagerComponent::IsVertical()
	{
		return vertical_;
	}
	void MenuManagerComponent::SetSpacing(Graphics::Vector4 spacingVal)
	{

		spacing_ = spacingVal;
	}
	void MenuManagerComponent::SetPosition(Graphics::Vector4 newPos)
	{
		pos_ = newPos;
	}
	Graphics::Vector4 MenuManagerComponent::GetPosition()
	{
		return pos_;
	}
	int MenuManagerComponent::GetIndicated()
	{
		return selected_;
	}
	Graphics::Vector4 MenuManagerComponent::GetSpacing()
	{
		return spacing_;
	}
}