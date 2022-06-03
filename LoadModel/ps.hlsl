struct PSInput {
	float4 svpos:SV_POSITION;
	float3 pos:POSITION;
	float3 norm:normal;
	float2 uv:TECOORD;
};

float4 main(PSInput input) : SV_TARGET
{
	return float4(input.norm, 1.0f);
}