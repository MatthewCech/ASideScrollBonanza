#include "InitializeLifeRandom.hpp"

ASSB::InitializeLifeRandom::InitializeLifeRandom(Globals::ObjectID owner, float min, float max)
	: Initializer(owner)
	, Min(min)
	, Max(max)
{
}

int ASSB::InitializeLifeRandom::Update(UpdateEvent *, ParticleBuffer::Particle & particle)
{
	float dist = Max - Min;

	float scale = Min + (rand() / static_cast<float>(RAND_MAX)) * dist;

	particle.life = scale;
	return 0;
}
