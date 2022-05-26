// �s�N�Z���V�F�[�_�̓���(��΂ɂ���)
struct PS_INPUT {
	float4 Diffuse				:COLOR0;		// �f�B�t���[�Y
	float4 Specular				:COLOR1;		// �X�y�L�����J���[
	float2 uv					:TEXCOORD0;		// �e�N�X�`�����W
};

// �s�N�Z���V�F�[�_�̏o��(��΂ɂ���)
struct PS_OUTPUT {
	float4 color				:SV_TARGET0;// �F
};

// �萔�o�b�t�@
cbuffer buff : register(b0) {
	float threshold;
	float angle;
}


SamplerState sam;// �T���v��
Texture2D tex:register(t0);
Texture2D ptn:register(t1);
Texture2D norm:register(t2);// �@���}�b�v
//�e�N�X�`��(�ő�W�܂łł���)
// 1�s�N�Z���P�s�N�Z���h��Ԃ�
PS_OUTPUT main(PS_INPUT input) {
	PS_OUTPUT output;
	float discval = ptn.Sample(sam, input.uv).r;
	float yedge = pow(1.0 - saturate(abs(threshold - input.uv.y)), 5);
	if (input.uv.y + (discval * yedge) < threshold) {
		// �������R�����g�A�E�g����ƃX�L�����݂����Ȃ��Ƃ��ł���
		discard;
	}
	// �m�[�}���}�b�v
	float3 lightVec = float3(cos(angle), -sin(angle), 0.5);
	lightVec = normalize(lightVec);
	float3 normal=norm.Sample(sam, input.uv).rgb;// nx,ny,nz
	normal = (normal * 2) - 1;
	normal = normalize(normal);
	normal.z = -normal.z;

	float bright = saturate(saturate(dot(-lightVec, normal))+0.25);

	float4 col = tex.Sample(sam, input.uv);//float4(input.uv, 0, 1);// �Ԃ�Ԃ�
	//float4 col = tex.Sample(sam, input.uv+float2(sin(angle)*0.5f,0));//float4(input.uv, 0, 1);// �Ԃ�Ԃ�
	output.color = col;
	if (col.a == 0.0) {
		discard;// �Ȃ��������Ƃɂ���
	}
	//float edge = 1.0 - saturate(abs(threshold - discval));
	float edge = saturate((1.0 - abs(input.uv.y + (yedge * discval) - threshold)));
	edge = pow(edge, 15);
	//output.color.rgb = 1.0 - col.rgb;
	//float mx = fmod(input.uv.x, 0.1) * 10;
	//float my = fmod(input.uv.y, 0.1) * 10;
	float m = fmod(input.uv.x+input.uv.y, 0.1) * 10;
	output.color.rgb = float3(1, 0, 1) * edge +
		(output.color.rgb* bright*m) * (1.0 - edge);
	//output.color.rgb = float3(1, 0, 1) * edge +
	//	(output.color.rgb* bright*mx * my) * (1.0 - edge);
	return output;
}