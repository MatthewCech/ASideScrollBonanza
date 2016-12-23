#include "Particle.hlsli"

static const float PI = 3.1415926535;

[maxvertexcount(6)]
void main(point GeoShaderInput Input[1], inout TriangleStream<PixelShaderInput> OutStream)
{
    PixelShaderInput output[4];

	output[0].color = Input[0].color;
	output[1].color = Input[0].color;
	output[2].color = Input[0].color;
	output[3].color = Input[0].color;

	float scale = Input[0].scale / 2;
	float rotation = Input[0].rotation + PI / 4;
		
	for (int i = 0; i < 4; ++i)
	{
        output[i].position = mul(Input[0].viewProjection, Input[0].position + float4(scale * cos(rotation), scale * sin(rotation), 0, 0));
        ;

		if(cos(rotation - Input[0].rotation) > 0)
			output[i].UV.x = 1;
		else
			output[i].UV.x = 0;

		if (sin(rotation - Input[0].rotation) > 0)
			output[i].UV.y = 0;
		else
			output[i].UV.y = 1;

		rotation += PI / 2;
	}

	OutStream.Append(output[0]);
	OutStream.Append(output[2]);
	OutStream.Append(output[1]);
	OutStream.RestartStrip();

	OutStream.Append(output[0]);
	OutStream.Append(output[3]);
	OutStream.Append(output[2]);
	OutStream.RestartStrip();
}