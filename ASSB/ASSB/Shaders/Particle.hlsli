
struct GeoShaderInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float rotation : ROTATION;
	float scale : SCALE;
};

struct PixelShaderInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 UV : TEXCOORD;
};
