#pragma once
#include "Component.hpp"
#include "Particles/ParticleBuffer.h"
#include "Events/UpdateEvent.hpp"
#include <memory>

namespace ASSB
{
	class Emitter;
	class Initializer;
	class Updater;
	class Terminator;

	class ParticleComponent : public Component
	{
	public:
		std::unique_ptr<Emitter> Emitter;
		std::vector<std::unique_ptr<Initializer>> Initializers;
		std::vector<std::unique_ptr<Updater>> Updaters;
		std::unique_ptr<Terminator> Terminator;
		std::wstring Path;
		ParticleBuffer Buffer;
		Graphics::GraphicsEngine::BlendMode BlendMode;
		bool Visible;


		ParticleComponent(Globals::ObjectID owner);
		ParticleComponent(const ParticleComponent &rhs);

		ParticleComponent &operator=(const ParticleComponent &rhs);
	private:

		void Update(UpdateEvent* e);
	};
}
