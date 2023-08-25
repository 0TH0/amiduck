#include "StarEffect.h"
#include "../Engine/VFX.h"
#include "../Engine/Audio.h"

void StarManager::StarEffect(XMFLOAT3 pos)
{
	EmitterData data;
	data.textureFileName = "Image\\star.png";
	data.position = pos;
	data.delay = 0;
	data.number = 50;
	data.lifeTime = 80;
	data.positionRnd = XMFLOAT3(0.4, 0, 0.4);
	data.direction = XMFLOAT3(0, -1, 0);
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

void StarManager::StarAudio()
{
	Audio::Play(Audio::Load("Audio/star.wav"));
}
