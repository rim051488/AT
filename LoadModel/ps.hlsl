struct PSInput {
	float4 svpos:SV_POSITION;
	float3 pos:POSITION;
	float3 norm:normal;
	float2 uv:TECOORD;
	float3 col:COLOR0;
};

float4 main(PSInput input) : SV_TARGET
{
	float3 light = float3(1,-1,1);
	light = normalize(light);
	float b = saturate(dot(input.norm, -light));
	return float4(input.col*b, 1.0f);
}