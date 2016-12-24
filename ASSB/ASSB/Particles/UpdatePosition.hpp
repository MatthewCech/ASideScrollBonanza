#pragma once
#include "Updater.hpp"
#include "Graphics/Vector4.h"


namespace ASSB
{
	class UpdatePosition : public Updater
	{
	public:
		Graphics::Vector4 Velocity;

		UpdatePosition(Globals::ObjectID owner, Graphics::Vector4 velocity = Graphics::Vector4(0,0,0));

		int Update(UpdateEvent* e, ParticleBuffer::Particle& particle) override;
	};
}