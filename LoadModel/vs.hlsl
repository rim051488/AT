struct VertexInput {
	float3 pos : POSITION;//���W
	float3 norm : NORMAL;//�@��
	float4 diffuse : COLOR0;
	float4 specular : COLOR1;
	float4 uv0 : TEXCOORD0;
	float4 uv1 : TEXCOORD1;
};

cbuffer BaseCBuffer : register(b1) {
	float4 AntiViewportM[4];//4*4
	float4 ProjectionM[4];//4*4
	float4 ViewM[3];//4*3(�J����)
	float4 localM[3];//4*3(��]�g�k���s�ړ�)
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