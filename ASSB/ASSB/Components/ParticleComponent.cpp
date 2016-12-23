#include "ParticleComponent.hpp"
#include "GameEngine/GameEngine.h"

namespace ASSB
{
	ParticleComponent::ParticleComponent(Globals::ObjectID owner) : Component(owner), Buffer(GameEngine::Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Instance->Graphics)
	{
		Path = L"../../../Assets/None.png";
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
}
