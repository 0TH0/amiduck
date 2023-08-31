#pragma once
#include "../Engine/GameObject.h"

namespace EffectManager
{
	void ElectricEffect(XMFLOAT3 pos);
	void BombEffect(XMFLOAT3 pos);
	void EnemyEffect(XMFLOAT3, XMFLOAT4 color);
	void TakeItemBoxEffect(XMFLOAT3 pos);
	void PopBridgeEffect(XMFLOAT3 pos);
	void StarEffect(XMFLOAT3 pos);
	void RiverEffect(XMFLOAT3 pos);
	void DieEffect(XMFLOAT3 pos);
};