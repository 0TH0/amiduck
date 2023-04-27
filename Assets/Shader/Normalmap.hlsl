Texture2D tex : register(t0);
SamplerState smp : register(s0);
Texture2D texNormal : register(t1);

cbuffer gloabal
{
	float4x4	g_matWVP;			// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	g_matNormalTrans;	// �@���̕ϊ��s��i��]�s��Ɗg��̋t�s��j
	float4x4	g_matWorld;			// ���[���h�ϊ��s��
	float4		g_vecLightDir;		// ���C�g�̕����x�N�g��
	float4		g_vecDiffuse;		// �f�B�t���[�Y�J���[�i�}�e���A���̐F�j
	float4		g_vecAmbient;		// �A���r�G���g�J���[�i�e�̐F�j
	float4		g_vecSpeculer;		// �X�y�L�����[�J���[�i�n�C���C�g�̐F�j
	float4		g_vecCameraPosition;// ���_�i�J�����̈ʒu�j
	float		g_shininess;		// �n�C���C�g�̋����i�e�J����j
	float		g_alpha;			//�����x
	float		g_scroll;
	bool		g_isTexture;		// �e�N�X�`���\���Ă��邩�ǂ���
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD;
	float4 color : COLOR0;
	float4 specular : COLOR1;
	float4 normal : NORMAL;
};

//���_�V�F�[�_
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	VS_OUT outData;
	outData.pos = mul(pos, g_matWVP);
	outData.uv = uv;

	float4 light = float4(1, 1, -1, 0);
	light = normalize(light);

	normal = mul(normal, g_matNormalTrans);
	normal.w = 0;
	outData.color = dot(normal, light);

	//�N�����v
	outData.color = clamp(outData.color, 0, 1);

	//�����x�N�g��
	float4 V = normalize(mul(pos, g_matWVP) - g_vecCameraPosition);
	float4 R = reflect(light, normal);

	outData.specular = 10 * pow(clamp(dot(R, V), 0, 1), g_shininess) * g_vecSpeculer;

	return outData;
}

//�s�N�Z���V�F�[�_
//�߂�l:float4 = �F
// : �Z�}���e�B�b�N ���̏�񂪉���
// SV�@�Ƃ�������2D
float4 PS(VS_OUT inData) : SV_TARGET
{
	float4 diffuse;
	float4 ambient;
	float4 specular;
	float alpha;

	if (g_isTexture)
	{
		diffuse = tex.Sample(smp, inData.uv) * inData.color;
		ambient = tex.Sample(smp, inData.uv) * 0.1;
		alpha = tex.Sample(smp, inData.uv).a;
	}
	else
	{
		diffuse = g_vecDiffuse* inData.color;
		ambient = g_vecDiffuse* 0.1;
		alpha = g_vecDiffuse.a;
	}

	specular = inData.specular;

	float4 result = diffuse + ambient + specular;
	result.a = alpha;

	return result;
}