Texture2D tex : register(t0);
SamplerState smp : register(s0);
Texture2D texNormal : register(t1);

cbuffer gloabal
{
	float4x4	g_matWVP;			// ワールド・ビュー・プロジェクションの合成行列
	float4x4	g_matNormalTrans;	// 法線の変換行列（回転行列と拡大の逆行列）
	float4x4	g_matWorld;			// ワールド変換行列
	float4		g_vecLightDir;		// ライトの方向ベクトル
	float4		g_vecDiffuse;		// ディフューズカラー（マテリアルの色）
	float4		g_vecAmbient;		// アンビエントカラー（影の色）
	float4		g_vecSpeculer;		// スペキュラーカラー（ハイライトの色）
	float4		g_vecCameraPosition;// 視点（カメラの位置）
	float		g_shininess;		// ハイライトの強さ（テカリ具合）
	float		g_alpha;			//透明度
	float		g_scroll;
	bool		g_isTexture;		// テクスチャ貼ってあるかどうか
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD;
	float4 color : COLOR0;
	float4 specular : COLOR1;
	float4 normal : NORMAL;
};

//頂点シェーダ
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

	//クランプ
	outData.color = clamp(outData.color, 0, 1);

	//視線ベクトル
	float4 V = normalize(mul(pos, g_matWVP) - g_vecCameraPosition);
	float4 R = reflect(light, normal);

	outData.specular = 10 * pow(clamp(dot(R, V), 0, 1), g_shininess) * g_vecSpeculer;

	return outData;
}

//ピクセルシェーダ
//戻り値:float4 = 色
// : セマンティック その情報が何か
// SV　といったら2D
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