#pragma once
#include "Component.hpp"
#include <string>
#include <vector>

namespace ASSB
{
	class SpriteComponent : public Component
	{
	public:
		bool Visible;

		SpriteComponent(Globals::ObjectID owner);
		SpriteComponent(const SpriteComponent &rhs);
		SpriteComponent &operator=(const SpriteComponent &rhs);
		void AddPath(std::wstring);
		void AddAltPath(std::wstring);
		std::wstring GetPath(bool isLight = true);
		void SetSwappable(bool isSwappable);
		bool IsSwappable();

	private:
		size_t frameIndex_;
		bool isLightDarkSwappable_;
		std::vector < std::wstring > paths_;
		std::vector < std::wstring > altPaths_;
	};
}
