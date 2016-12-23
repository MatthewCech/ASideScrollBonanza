#include "SpriteComponent.hpp"

namespace ASSB
{
	SpriteComponent::SpriteComponent(Globals::ObjectID owner) : Component(owner)
	{
		Visible = true;
		Path = L"../../../Assets/None.png";
	}

	SpriteComponent::SpriteComponent(const SpriteComponent & rhs) : Component(rhs.Owner)
	{
		*this = rhs;
	}

	SpriteComponent & SpriteComponent::operator=(const SpriteComponent & rhs)
	{
		Visible = rhs.Visible;
		Path = rhs.Path;
		return *this;
	}

}
