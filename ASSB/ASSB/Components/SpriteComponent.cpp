#include "SpriteComponent.hpp"

namespace ASSB
{
	SpriteComponent::SpriteComponent(const SpriteComponent & rhs)
	{
		Path = rhs.Path;
	}

	SpriteComponent & SpriteComponent::operator=(const SpriteComponent & rhs)
	{
		Path = rhs.Path;
		return *this;
	}

	SpriteComponent::SpriteComponent()
	{
		Path = L"../../../Assets/None.png";
	}
}
