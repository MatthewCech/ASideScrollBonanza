#include "SpriteComponent.hpp"

namespace ASSB
{
	// Ctors and assignment
	SpriteComponent::SpriteComponent(Globals::ObjectID owner)
		: Component(owner)
		, Visible(true)
		, frameIndex_(0)
		, isLightDarkSwappable_(false)
		, paths_()
		, altPaths_()
	{  }

	SpriteComponent::SpriteComponent(const SpriteComponent & rhs) : Component(rhs.Owner)
	{
		*this = rhs;
	}

	SpriteComponent & SpriteComponent::operator=(const SpriteComponent & rhs)
	{
		if (this != &rhs)
		{
			Visible = rhs.Visible;
			isLightDarkSwappable_ = rhs.isLightDarkSwappable_;
			paths_ = rhs.paths_;
			altPaths_ = rhs.altPaths_;
		}
		return *this;
	}

	void SpriteComponent::AddPath(std::wstring path)
	{
		paths_.push_back(path);
	}

	void SpriteComponent::AddAltPath(std::wstring path)
	{
		altPaths_.push_back(path);
	}

	std::wstring SpriteComponent::GetPath(bool isLight)
	{
		if (!isLightDarkSwappable_)
		{
			if (paths_.size() == 0)
				return L"../../../Assets/None.png";

			return paths_[frameIndex_];
		}
		else
		{
			if (isLight)
			{
				if (paths_.size() == 0)
					return L"../../../Assets/None.png";

				return paths_[frameIndex_];
			}
			else
			{
				if (altPaths_.size() == 0)
					return L"../../../Assets/None.png";

				return altPaths_[frameIndex_];
			}
		}
	}

	void SpriteComponent::SetSwappable(bool isSwappable)
	{
		isLightDarkSwappable_ = isSwappable;
	}

	bool SpriteComponent::IsSwappable()
	{
		return isLightDarkSwappable_;
	}
}
