#pragma once
#include "Terminator.hpp"

namespace ASSB
{
	class TerminateInstant : public Terminator
	{
	public:

		TerminateInstant(Globals::ObjectID owner);

		int Update(UpdateEvent* e, ParticleBuffer::Particle& particle);
	};
}
