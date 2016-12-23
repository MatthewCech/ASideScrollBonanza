#include "ParticleBuffer.h"

namespace ASSB
{
	ParticleBuffer::ParticleBuffer(Graphics::GraphicsEngine & graphics, size_t maxParticles)
		: Graphics(&graphics)
		, Dirty(false)
		, MaxParticles(maxParticles)
	{
		Particles.reserve(maxParticles);
	}

	void ParticleBuffer::Use() const
	{
		if (Dirty)
			Update();

		ID3D11DeviceContext3* dc = Graphics->DeviceContext.Get();

		dc->IASetInputLayout(Layout.Get());
		UINT stride = sizeof(Particle);
		UINT offset = 0;
		dc->IASetVertexBuffers(0, 1, VertBuffer.GetAddressOf(), &stride, &offset);
		dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		//no index buffer
		dc->IASetIndexBuffer(nullptr, DXGI_FORMAT::DXGI_FORMAT_UNKNOWN, 0);
	}

	bool ParticleBuffer::Create(const Graphics::Shader & shader)
	{
		pShader = &shader;
		//define the vertex buffer
		D3D11_BUFFER_DESC vbDesc{};
		vbDesc.ByteWidth = static_cast<UINT>(sizeof(Particle) * MaxParticles);
		vbDesc.StructureByteStride = sizeof(Particle);
		vbDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;

		vbDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		vbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA vbData{};
		vbData.pSysMem = Particles.data();

		//create the vertex buffer
		HRESULT hr = Graphics->Device->CreateBuffer(&vbDesc, &vbData, VertBuffer.ReleaseAndGetAddressOf());
		if (FAILED(hr))
			return false;

		//create the layout
		D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
		{
			/*name       index             format           input slot      alignedByteOffset          InputSlotClass             InstanceDataStepRate*/
			{ "POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "ROTATION", 0, DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "SCALE", 0, DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "LIFE", 0, DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		if (FAILED(Graphics->Device->CreateInputLayout(layoutDesc, _ARRAYSIZE(layoutDesc), shader.ByteCode->GetBufferPointer(), shader.ByteCode->GetBufferSize(), Layout.ReleaseAndGetAddressOf())))
			return false;

		return true;
	}

	size_t ParticleBuffer::size()
	{
		return Particles.size();
	}

	void ParticleBuffer::Remove(size_t index)
	{
		std::swap(Particles[index], Particles[Particles.size() - 1]);
		Particles.pop_back();
		Dirty = true;
	}

	ParticleBuffer::Particle& ParticleBuffer::Add()
	{
		Dirty = true;

		if (Particles.size() < MaxParticles)
		{
			Particles.emplace_back();
			auto& part = Particles[Particles.size() - 1];
			part.Color[0] = 1;
			part.Color[1] = 1;
			part.Color[2] = 1;
			part.Color[3] = 1;
		}

		return Particles[Particles.size() - 1];
	}

	const ParticleBuffer::Particle & ParticleBuffer::operator[](size_t index) const
	{
		return Particles[index];
	}

	ParticleBuffer::Particle & ParticleBuffer::operator[](size_t index)
	{
		Dirty = true;
		return Particles[index];
	}

	bool ParticleBuffer::Update() const
	{
		//lock access to the buffer on the GPU
		D3D11_MAPPED_SUBRESOURCE mappedResource{};
		HRESULT res = Graphics->DeviceContext->Map(VertBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(res))
			return false;

		//update the buffer
		memcpy(mappedResource.pData, Particles.data(), sizeof(Particle) * Particles.size());

		//let the GPU play with it again
		Graphics->DeviceContext->Unmap(VertBuffer.Get(), 0);

		const_cast<ParticleBuffer*>(this)->Dirty = false;
		return true;
	}
}

