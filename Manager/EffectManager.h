#pragma once
#include "../Engine/GameObject.h"

namespace EffectManager
{
	//電気
	void ElectricEffect(XMFLOAT3 pos);
	//爆弾
	void BombEffect(XMFLOAT3 pos);
	//敵
	void EnemyEffect(XMFLOAT3, XMFLOAT4 color);
	//アイテム
	void TakeItemBoxEffect(XMFLOAT3 pos);
	//橋
	void PopBridgeEffect(XMFLOAT3 pos);
	//星
	void StarEffect(XMFLOAT3 pos);
	//川
	void RiverEffect(XMFLOAT3 pos);
	//死んだ
	void DieEffect(XMFLOAT3 pos);
};