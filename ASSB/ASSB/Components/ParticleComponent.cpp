#include "ParticleComponent.hpp"
#include "GameEngine/GameEngine.h"
#include "Particles/Emitter.hpp"
#include "Particles/Initializer.hpp"
#include "Particles/Updater.hpp"
#include "Particles/Terminator.hpp"

namespace ASSB
{
	ParticleComponent::ParticleComponent(Globals::ObjectID owner) : Component(owner), Buffer(GameEngine::Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Graphics)
	{
		Path = L"../../../Assets/None.png";
		Connect(this, &ParticleComponent::Update);
		Buffer.Create(GameEngine::Instance->ParticleVertexShader);
	}

	ParticleComponent::ParticleComponent(const ParticleComponent & rhs) 
		: Component(rhs.Owner)
		, Buffer(GameEngine::Instance->Graphics)
	{
		*this = rhs;
	}

	ParticleComponent & ASSB::ParticleComponent::operator=(const ParticleComponent & rhs)
	{
		Buffer = rhs.Buffer;
		Buffer.Create(*rhs.Buffer.pShader);
		Path = rhs.Path;
		return *this;
	}

	void ParticleComponent::Update(UpdateEvent * e)
	{
		int made = 0;
		if (Emitter)
			made = Emitter->Update(e);

		for (int i = 0; i < made; ++i)
		{
			for (auto& Initializer : Initializers)
			{
				Initializer->Update(e, Buffer[Buffer.size() - 1 - i]);
			}
		}
		for (size_t i = 0; i < Buffer.size(); ++i)
		{
			ParticleBuffer::Particle& part = Buffer[i];
			for (auto& Updater : Updaters)
			{
				Updater->Update(e, part);
			}
			part.life -= e->Time.DT;

			if (Terminator)
			{
				int del = Terminator->Update(e, part);

				if (del)
				{
					Buffer.Remove(i);
					--i;
					continue;
				}
			}
		}
	}
}
