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
SamplerState sam;// �T���v��
Texture2D tex;//�e�N�X�`��
// 1�s�N�Z���P�s�N�Z���h��Ԃ�
PS_OUTPUT main(PS_INPUT input) {
	PS_OUTPUT output;
	output.color = float4(input.uv, 1, 1);// �Ԃ�Ԃ�
	return output;
}