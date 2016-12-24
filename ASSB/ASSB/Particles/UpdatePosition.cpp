#include "UpdatePosition.hpp"

ASSB::UpdatePosition::UpdatePosition(Globals::ObjectID owner, Graphics::Vector4 velocity)
	: Updater(owner)
	, Velocity(velocity)
{

}

int ASSB::UpdatePosition::Update(UpdateEvent * e, ParticleBuffer::Particle & particle)
{
	float dt = static_cast<float>(e->Time.DT);

	Graphics::Vector4 vec = Graphics::Vector4(particle.Position[0], particle.Position[1], particle.Position[2]);

	vec += Velocity * dt;

	particle.Position[0] = vec.X;
	particle.Position[1] = vec.Y;
	particle.Position[2] = vec.Z;

	return 0;
}
