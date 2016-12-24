#pragma once
#include "Emitter.hpp"

namespace ASSB
{
	class EmitConstant : public Emitter
	{
	public:
		float ParticlesPerSecond;

		EmitConstant(Globals::ObjectID owner, float particlesPerSecond);
		virtual int Update(UpdateEvent* e) override;
	private:
		float ParticlesThisFrame;
	};
}