#pragma once
#include "Component.hpp"
#include "Particles/ParticleBuffer.h"

namespace ASSB
{
	class ParticleComponent : public Component
	{
	public:
		std::wstring Path;
		ParticleBuffer Buffer;
		Graphics::GraphicsEngine::BlendMode BlendMode;

		ParticleComponent(Globals::ObjectID owner);
		ParticleComponent(const ParticleComponent &rhs);

		ParticleComponent &operator=(const ParticleComponent &rhs);
	private:
	};
}
