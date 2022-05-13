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
SamplerState sam;// サンプラ
Texture2D tex;//テクスチャ(最大８個までできる)
// 1ピクセル１ピクセル塗りつぶし
PS_OUTPUT main(PS_INPUT input) {
	PS_OUTPUT output;
	output.color = tex.Sample(sam,input.uv);//float4(input.uv, 0, 1);// 赤を返す
	output.color.rgb = 1.0 - output.color.rgb;
	return output;
}