#pragma once
#include "Initializer.hpp"
#include "Graphics/Vector4.h"

namespace ASSB
{
	class InitializePositionRandom : public Initializer
	{
	public:
		Graphics::Vector4 Min;
		Graphics::Vector4 Max;

		InitializePositionRandom(Globals::ObjectID owner, Graphics::Vector4 min, Graphics::Vector4 max);

		int Update(UpdateEvent* e, ParticleBuffer::Particle& particle) override;
	};
}