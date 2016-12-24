#include "InitializePositionRandom.hpp"

ASSB::InitializePositionRandom::InitializePositionRandom(Globals::ObjectID owner, Graphics::Vector4 min, Graphics::Vector4 max)
	: Initializer(owner)
	, Min(min)
	, Max(max)
{

}

int ASSB::InitializePositionRandom::Update(UpdateEvent *, ParticleBuffer::Particle & particle)
{
	float distx = Max.X - Min.X;
	float posx = Min.X + distx * (rand() / static_cast<float>(RAND_MAX));
	float disty = Max.Y - Min.Y;
	float posy = Min.Y + disty * (rand() / static_cast<float>(RAND_MAX));
	float distz = Max.Z - Min.Z;
	float posz = Min.Z + distz * (rand() / static_cast<float>(RAND_MAX));

	particle.Position[0] = posx;
	particle.Position[1] = posy;
	particle.Position[2] = posz;

	return 0;
}
