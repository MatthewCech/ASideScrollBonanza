#pragma once
#include "Initializer.hpp"

namespace ASSB
{
	class InitializeLifeRandom : public Initializer
	{
	public:
		float Min;
		float Max;

		InitializeLifeRandom(Globals::ObjectID owner, float min, float max);

		int Update(UpdateEvent* e, ParticleBuffer::Particle& particle) override;
	};
}