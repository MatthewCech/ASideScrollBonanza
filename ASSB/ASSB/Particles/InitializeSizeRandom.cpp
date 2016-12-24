#include "InitializeSizeRandom.hpp"

namespace ASSB
{
	InitializeSizeRandom::InitializeSizeRandom(Globals::ObjectID owner, float min, float max)
		: Initializer(owner)
		, Min(min)
		, Max(max)
	{

	}

	int InitializeSizeRandom::Update(UpdateEvent *, ParticleBuffer::Particle & particle)
	{
		float dist = Max - Min;

		float scale = Min + (rand() / static_cast<float>(RAND_MAX)) * dist;

		particle.Scale = scale;
		return 0;
	}
}
