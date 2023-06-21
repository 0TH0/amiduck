#include "PlayerEffect.h"
#include "Engine/VFX.h"

namespace PlayerEffect
{
	void Bomb(XMFLOAT3 pos)
	{
		EmitterData data;
		data.textureFileName = "Particle/Cloud.png";
		data.position = pos;
		data.position.y += 4;
		data.delay = 0;
		data.number = 180;
		data.lifeTime = 50;
		data.direction = XMFLOAT3(0, 0, 1);
		data.directionRnd = XMFLOAT3(0, 360, 0);
		data.speed = 0.2f;
		data.speedRnd = 0.45f;
		data.size = XMFLOAT2(1.0f, 1.0f);
		data.sizeRnd = XMFLOAT2(0.4f, 0.4f);
		data.scale = XMFLOAT2(1.05f, 1.05f);
		data.color = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.2f);
		data.deltaColor = XMFLOAT4(0.0f, 0.0f, 0.0f, -0.004f);
		VFX::Start(data);
	}
}