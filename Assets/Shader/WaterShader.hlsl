//───────────────────────────────────────
 // テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D tex : register(t0);
SamplerState smp : register(s0);
Texture2D normalTex : register(t1);

//───────────────────────────────────────
 // コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global
{
	float4x4	g_matWVP;			// ワールド・ビュー・プロジェクションの合成行列
	float4x4	g_matNormalTrans;	// 法線の変換行列（回転行列と拡大の逆行列）
	float4x4	g_matWorld;			// ワールド変換行列
	float4		g_vecLightDir;		// ライトの方向ベクトル
	float4		g_vecDiffuse;		// ディフューズカラー（マテリアルの色）
	float4		g_vecAmbient;		// アンビエントカラー（影の色）
	float4		g_vecSpeculer;		// スペキュラーカラー（ハイライトの色）
	float4		g_vecCameraPosition;// 視点（カメラの位置）
	float		g_shuniness;		// ハイライトの強さ（テカリ具合）
	float		g_alpha;			//透明度
	float		g_scroll;
	bool		g_isTexture;		// テクスチャ貼ってあるかどうか
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD;
	float4 V : TEXCOORD1;
	float4 light : TEXCOORD2;
};

//頂点シェーダー
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL, float4 tangent : TANGENT)
{
	VS_OUT outData;
	outData.pos = mul(pos, g_matWVP);
	outData.uv = uv;

	float3 binormal = cross(normal, tangent);

	normal.w = 0;
	normal = mul(normal, g_matNormalTrans);
	normal = normalize(normal);

	tangent.w = 0;
	tangent = mul(tangent, g_matNormalTrans);
	tangent = normalize(tangent);

	binormal = mul(binormal, g_matNormalTrans);
	binormal = normalize(binormal);


	float4 eye = normalize(mul(pos, g_matWorld) - g_vecCameraPosition);
	outData.V.x = dot(eye, tangent);
	outData.V.y = dot(eye, binormal);
	outData.V.z = dot(eye, normal);
	outData.V.w = 0;

	float4 light = float4(1, 3, 1, 0);
	light = normalize(light);
	outData.light.x = dot(light, tangent);
	outData.light.y = dot(light, binormal);
	outData.light.z = dot(light, normal);
	outData.light.w = 0;

	return outData;
}

//ピクセルシェーダー
float4 PS(VS_OUT inData) : SV_TARGET
{
	inData.light = normalize(inData.light);

	float4 diffuse;
	float4 ambient;
	float4 specular;

	float2 uv1 = inData.uv;
	uv1.x += g_scroll;
	float4 normal1 = normalTex.Sample(smp, uv1) * 2 - 1;

	float2 uv2 = inData.uv;
	uv2.x -= g_scroll * 0.3;
	uv2.y *= 1.2;
	float4 normal2 = normalTex.Sample(smp, uv2) * 2 - 1;

	float4 normal = normal1 + normal2;

	normal.w = 0;
	normal = normalize(normal);


	float4 S = dot(inData.light,normal);
	S = clamp(S, 0, 1);


	float4 R = reflect(inData.light, normal);
	specular = pow(clamp(dot(R, inData.V), 0, 1), 5) * 3;

	float alpha;

	if (g_isTexture)
	{
		diffuse = tex.Sample(smp, inData.uv) * S;
		ambient = tex.Sample(smp, inData.uv) * 0.2;
		alpha = tex.Sample(smp, inData.uv).a;
	}
	else
	{
		diffuse = g_vecDiffuse * S;
		ambient = g_vecDiffuse * 0.2;
		alpha = g_vecDiffuse.a;
	}

	float4 result = diffuse + ambient + specular;

	result.a = 1;

	return result;
}