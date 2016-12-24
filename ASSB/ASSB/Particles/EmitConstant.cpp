#include "EmitConstant.hpp"

namespace ASSB
{
	EmitConstant::EmitConstant(Globals::ObjectID owner, float particlesPerSecond)
		: Emitter(owner)
		, ParticlesPerSecond(particlesPerSecond)
	{

	}

	int EmitConstant::Update(UpdateEvent * e)
	{
		ParticlesThisFrame += static_cast<float>(e->Time.DT * ParticlesPerSecond);
		int ParticlesMade = 0;

		while (ParticlesThisFrame > 1)
		{
			Comp->Buffer.Add();
			++ParticlesMade;
			ParticlesThisFrame -= 1;
		}

		return ParticlesMade;
	}
}
