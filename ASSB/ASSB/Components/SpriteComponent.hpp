#pragma once
#include "Component.hpp"
#include <string>

namespace ASSB
{
	class SpriteComponent : public Component
	{
	public:
		bool Visible;
		std::wstring Path;

		SpriteComponent(Globals::ObjectID owner);
		SpriteComponent(const SpriteComponent &rhs);
		SpriteComponent &operator=(const SpriteComponent &rhs);

	};
}
