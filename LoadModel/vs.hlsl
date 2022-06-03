struct VertexInput {
	float3 pos : POSITION;//座標
	float3 norm : NORMAL;//法線
	float4 diffuse : COLOR0;
	float4 specular : COLOR1;
	float4 uv0 : TEXCOORD0;
	float4 uv1 : TEXCOORD1;
};

cbuffer BaseCBuffer : register(b1) {
	float4 AntiViewportM[4];//4*4
	float4 ProjectionM[4];//4*4
	float4 ViewM[3];//4*3(カメラ)
	float4 localM[3];//4*3(回転拡縮平行移動)
	float4 ToonOutLineSize;// トゥーンの輪郭線の大きさ
	float DiffuseSource; //ディフューズカラー(0.0f:マテリアル 1.0f : 頂点)
	float SpecularSource;// スペキュラカラー(0.0f:マテリアル 1.0f : 頂点)
	float MulSpecularColor;// スペキュラカラー値に乗算する値(スペキュラ無効処理で使用)
	float Padding;//詰め物(無視)
}

struct VSOutput {
	float4 svpos:SV_POSITION;
	float3 pos:POSITION;
	float3 norm:normal;
	float2 uv:TECOORD;
};

VSOutput main(VertexInput input)
{
	VSOutput output;
	float4 pos = float4(input.pos,1);

	pos.x = dot(pos, localM[0]);
	pos.y = dot(pos, localM[1]);
	pos.z = dot(pos, localM[2]);

	pos.x = dot(pos, ViewM[0]);
	pos.y = dot(pos, ViewM[1]);
	pos.z = dot(pos, ViewM[2]);

	pos.x = dot(pos, ProjectionM[0]);
	pos.y = dot(pos, ProjectionM[1]);
	pos.z = dot(pos, ProjectionM[2]);
	pos.w = dot(pos, ProjectionM[3]);
	output.svpos = pos;
	output.pos = input.pos;
	output.uv = input.uv0.xy;
	output.norm = input.norm;
	return output;
}