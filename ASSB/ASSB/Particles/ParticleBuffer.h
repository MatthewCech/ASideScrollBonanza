#pragma once
#include "Graphics/GraphicsEngine.h"
#include "Graphics/Shaders/Shader.h"

#pragma warning(push, 0)
#include <d3d11_4.h>
#include <wrl.h>
#include <vector>
#pragma warning(pop)

namespace ASSB
{
	struct ParticleBuffer
	{
	public:
		struct Particle
		{
			float Position[3];
			float Color[4];
			float Rotation;
			float Scale;
			float life;
		};

		ComPtr<ID3D11Buffer> VertBuffer;
		ComPtr<ID3D11InputLayout> Layout;

		ParticleBuffer(Graphics::GraphicsEngine& graphics, size_t maxParticles = 1000);
		
		const Particle& operator[](size_t index) const;
		Particle& operator[](size_t index);

		void Use();
		bool Create(const Graphics::Shader& shader);
		size_t size();
		void Remove(size_t index);
		Particle& Add();

	private:
		Graphics::GraphicsEngine* Graphics;
		const Graphics::Shader* pShader;
		bool Dirty;
		std::vector<Particle> Particles;
		size_t MaxParticles;

		bool Update();
	};
}
