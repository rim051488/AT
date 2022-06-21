struct VertexInput {
	float3 pos : POSITION;//���W
	float3 norm : NORMAL;//�@��
	float4 diffuse : COLOR0;
	float4 specular : COLOR1;
	float4 uv0 : TEXCOORD0;
	float4 uv1 : TEXCOORD1;
	float3 tangent:TANGENT;//�ڃx�N�g��
	float3 binormal:BINORMAL;//�]�@��
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
	float3 norm:NORMAL;
	float2 uv:TECOORD;
	float3 col:COLOR0;
	float3 tan:TANGENT;
	float3 bin:BINORMAL;
};

VSOutput main(VertexInput input)
{
	VSOutput output;
	float4 pos = float4(input.pos,1);

	pos.xyz = mul(pos, localM);//���[���h
	pos.xyz = mul(pos, viewM);//�r���[
	pos = mul(pos, ProjectionM);//�v���W�F�N�V����

	//�@���ɂ���]�����͏�Z���悤
	float3 norm = mul(input.norm, localM);
	float3 tan = mul(input.tangent, localM);
	float3 bin = mul(input.binormal, localM);

	output.svpos = pos;
	output.pos = input.pos;
	output.uv = input.uv0.xy;
	output.norm = normalize(norm);
	output.col = input.diffuse.rgb;
	output.tan = normalize(tan);
	output.bin = normalize(bin);
	return output;
}