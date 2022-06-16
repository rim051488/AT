struct VertexInput {
	float3 pos : POSITION;//���W
	float3 norm : NORMAL;//�@��
	float4 diffuse : COLOR0;
	float4 specular : COLOR1;
	float4 uv0 : TEXCOORD0;
	float4 uv1 : TEXCOORD1;
};

cbuffer BaseCBuffer : register(b1) {
	matrix AntiViewportM;//4*4�r���[�|�[�g�t�s��
	matrix ProjectionM;//�v���W�F�N�V�����s��
	float4x3 viewM;//4*3(�r���[�s��)
	float4x3 localM;//4*3(��]�g�k���s�ړ�)
	float4 ToonOutLineSize;// �g�D�[���̗֊s���̑傫��
	float DiffuseSource; //�f�B�t���[�Y�J���[(0.0f:�}�e���A�� 1.0f : ���_)
	float SpecularSource;// �X�y�L�����J���[(0.0f:�}�e���A�� 1.0f : ���_)
	float MulSpecularColor;// �X�y�L�����J���[�l�ɏ�Z����l(�X�y�L�������������Ŏg�p)
	float Padding;//�l�ߕ�(����)
}

struct VSOutput {
	float4 svpos:SV_POSITION;
	float3 pos:POSITION;
	float3 norm:normal;
	float2 uv:TECOORD;
	float3 col:COLOR0;
};

VSOutput main(VertexInput input)
{
	VSOutput output;
	float4 pos = float4(input.pos,1);

	pos.xyz = mul(pos, localM);
	pos.xyz = mul(pos, viewM);
	pos = mul(pos, ProjectionM);

	float3 norm = mul(input.norm, localM);

	output.svpos = pos;
	output.pos = input.pos;
	output.uv = input.uv0.xy;
	output.col = input.diffuse.xyz;
	output.norm = normalize(norm);
	return output;
}