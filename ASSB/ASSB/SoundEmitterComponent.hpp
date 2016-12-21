#pragma once
#include "Component.hpp" // Component



namespace ASSB
{
	class SoundEmitterComponent : public Component
	{
	public:
		SoundEmitterComponent();
		// SoundEmitterComponent

	private:

		// Omit
		SoundEmitterComponent &operator=(const SoundEmitterComponent &rhs) = delete;
		SoundEmitterComponent(const SoundEmitterComponent *rhs) = delete;
	};
}