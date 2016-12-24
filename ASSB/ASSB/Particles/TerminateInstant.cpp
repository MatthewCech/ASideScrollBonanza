#include "TerminateInstant.hpp"

ASSB::TerminateInstant::TerminateInstant(Globals::ObjectID owner) : Terminator(owner) {}

int ASSB::TerminateInstant::Update(UpdateEvent *, ParticleBuffer::Particle & particle)
{
	if (particle.life <= 0)
		return 1;
	return 0;
}
