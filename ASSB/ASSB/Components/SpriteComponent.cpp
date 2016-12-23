#include "SpriteComponent.hpp"

namespace ASSB
{
	SpriteComponent::SpriteComponent(const SpriteComponent & rhs)
	{
		*this = rhs;
	}

	SpriteComponent & SpriteComponent::operator=(const SpriteComponent & rhs)
	{
		Visible = rhs.Visible;
		Path = rhs.Path;
		return *this;
	}

	SpriteComponent::SpriteComponent()
	{
		Visible = true;
		Path = L"../../../Assets/None.png";
	}
}
