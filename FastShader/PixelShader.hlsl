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
float threshold : register(c0);


SamplerState sam;// サンプラ
Texture2D tex:register(t0);
Texture2D ptn:register(t1);
//テクスチャ(最大８個までできる)
// 1ピクセル１ピクセル塗りつぶし
PS_OUTPUT main(PS_INPUT input) {
	PS_OUTPUT output;
	float discval = ptn.Sample(sam, input.uv).r;
	if (discval > threshold) {
		discard;
	}
	float4 col = tex.Sample(sam, input.uv);//float4(input.uv, 0, 1);// 赤を返す
	output.color = col;
	if (col.a == 0.0) {
		discard;// なかったことにする
	}
	output.color.rgb = 1.0 - col.rgb;
	return output;
}