#include "Particle.hlsli"

struct VertexShaderInput
{
	float3 position : POSITION;
	float4 color : COLOR;
	float rotation : ROTATION;
	float scale : SCALE;
};

cbuffer ViewProjectionConstantBuffer : register(b0)
{
	matrix view;
	matrix viewProjection;
};

GeoShaderInput main(VertexShaderInput input)
{
	GeoShaderInput output;

	float4 pos = float4(input.position, 1.0f);
	output.position = pos;
	output.color = input.color;
	output.rotation = input.rotation;
	output.scale = input.scale;
    output.view = view;
    output.viewProjection = viewProjection;

	return output;
}
