#pragma once
#include <DirectXMath.h>

using namespace DirectX;

namespace Math
{
	//XMFLOAT4をセットする
	void SetXMFLOAT4(XMFLOAT4 xmf4, float x, float y, float z, float w);

	//XMFLOAT3をセットする
	void SetXMFLOAT3(XMFLOAT3 xmf4, float x, float y, float z);

	XMINT3 ToXMINT(XMFLOAT3 vec);

	//a以上b以下のランダム数字
	int RandInt(int a, int b);
};