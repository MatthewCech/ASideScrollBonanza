
struct GeoShaderInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float rotation : ROTATION;
	float scale : SCALE;
    matrix view : TRANSFORM;
    matrix viewProjection : PROJECTION;
};

struct PixelShaderInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 UV : TEXCOORD;
};
