#include "BombEffect.h"
#include "../Engine/VFX.h"

namespace BombEffect
{
	void BombEffect(XMFLOAT3 pos)
	{
		EmitterData data;
		data.textureFileName = "Particle\\Cloud.png";
        data.delay = 0;
        data.number = 1;
        data.lifeTime = 10;
        data.direction = XMFLOAT3(1, 0, 0);
        data.speed = 0.4f;
        data.speedRnd = 1;
        data.size = XMFLOAT2(3, 3);
        data.sizeRnd = XMFLOAT2(0, 0);
        data.scale = XMFLOAT2(1.05, 1.05);
        data.color = XMFLOAT4(1, 0, 0, 1);
        data.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);
        data.gravity = 0.003f;
        data.color = XMFLOAT4(0.5, 0.5, 0, 1);
		data.position = pos;
		VFX::Start(data);
	}
}