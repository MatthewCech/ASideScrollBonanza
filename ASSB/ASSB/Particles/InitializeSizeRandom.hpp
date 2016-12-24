#pragma once
#include "Initializer.hpp"

namespace ASSB
{
	class InitializeSizeRandom : public Initializer
	{
	public:
		float Min;
		float Max;

		InitializeSizeRandom(Globals::ObjectID owner, float min, float max);

		int Update(UpdateEvent* e, ParticleBuffer::Particle& particle) override;
	};
}