// ピクセルシェーダの入力(絶対にいる)
struct PS_INPUT {
	float4 Diffuse				:COLOR0;		// ディフューズ
	float4 Specular				:COLOR1;		// スペキュラカラー
	float2 uv					:TEXCOORD0;		// テクスチャ座標
};

// ピクセルシェーダの出力(絶対にいる)
struct PS_OUTPUT {
	float4 color				:SV_TARGET0;// 色
};

// 定数バッファ
cbuffer buff : register(b0) {
	float threshold;
	float angle;
}


SamplerState sam;// サンプラ
Texture2D tex:register(t0);
Texture2D ptn:register(t1);
Texture2D norm:register(t2);// 法線マップ
//テクスチャ(最大８個までできる)
// 1ピクセル１ピクセル塗りつぶし
PS_OUTPUT main(PS_INPUT input) {
	PS_OUTPUT output;
	float discval = ptn.Sample(sam, input.uv).r;
	float yedge = pow(1.0 - saturate(abs(threshold - input.uv.y)), 5);
	if (input.uv.y + (discval * yedge) < threshold) {
		// ここをコメントアウトするとスキャンみたいなことができる
		discard;
	}
	float3 lightVec = float3(cos(angle), -sin(angle), 0.5);
	lightVec = normalize(lightVec);
	float3 normal=norm.Sample(sam, input.uv).rgb;
	normal = (normal * 2) - 1;
	normal = normalize(normal);
	normal.z = -normal.z;

	float bright = saturate(saturate(dot(-lightVec, normal))+0.25);

	float4 col = tex.Sample(sam, input.uv);//float4(input.uv, 0, 1);// 赤を返す
	//float4 col = tex.Sample(sam, input.uv+float2(sin(angle)*0.5f,0));//float4(input.uv, 0, 1);// 赤を返す
	output.color = col;
	if (col.a == 0.0) {
		discard;// なかったことにする
	}
	float edge = 1.0 - saturate(abs(threshold - discval));
	edge = saturate((1.0 - abs(input.uv.y + (yedge * discval) - threshold)));
	edge = pow(edge, 15);
	//output.color.rgb = 1.0 - col.rgb;
	output.color.rgb = float3(1, 0, 1) * edge +
		(output.color.rgb* bright) * (1.0 - edge);
	return output;
}