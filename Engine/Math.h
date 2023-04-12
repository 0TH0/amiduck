#pragma once
#include <DirectXMath.h>

using namespace DirectX;

namespace Math
{
	//XMFLOAT4をセットする
	void SetXMFLOAT4(XMFLOAT4 xmf4, float x, float y, float z, float w);

	//XMFLOAT3をセットする
	void SetXMFLOAT3(XMFLOAT3 xmf4, float x, float y, float z);

	//XMFLOAT3からXMINT3
	XMINT3 ToXMINT(XMFLOAT3 vec);

	//a以上b以下のランダム数字
	int RandInt(int a, int b);

	//XMFLOAT3同士の引き算
	XMFLOAT3 SubXMFLOAT3(XMFLOAT3 vec, XMFLOAT3 vec2);

	//距離を求める
	float CalcDist(XMFLOAT3 vec, XMFLOAT3 vec2);

	//XMVECTORからXMFLOAT3に変換
	XMFLOAT3 VectorToFloat3(XMVECTOR v);
};