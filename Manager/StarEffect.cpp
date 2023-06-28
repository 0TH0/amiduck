#include "StarEffect.h"
#include "../Engine/VFX.h"

void StarEffect::TakeStarEffect(XMFLOAT3 pos)
{
	EmitterData data;
	data.textureFileName = "Image\\star.png";
	data.position = pos;
	data.delay = 0;
	data.number = 80;
	data.lifeTime = 100;
	data.positionRnd = XMFLOAT3(0.4, 0, 0.4);
	data.direction = XMFLOAT3(0, 1, 0);
	data.directionRnd = XMFLOAT3(90, 90, 90);
	data.speed = 0.25f;
	data.speedRnd = 1;
	data.accel = 0.93;
	data.size = XMFLOAT2(0.4, 0.4);
	data.sizeRnd = XMFLOAT2(0.4, 0.4);
	data.scale = XMFLOAT2(1, 1);
	data.color = XMFLOAT4(1, 1, 1, 1);
	data.deltaColor = XMFLOAT4(0, 0, 0, 0);
	data.gravity = 0.003f;
	VFX::Start(data);
}