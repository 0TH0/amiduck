#include "ItemBoxEffect.h"
#include "../Engine/VFX.h"

namespace ItemBoxEffect
{
    void TakeItemBoxEffect(XMFLOAT3 pos)
    {
        EmitterData data;

		data.textureFileName = "Image\\question_white.png";

		data.delay = 0;
		data.number = 80;
		data.lifeTime = 100;
		data.position = pos;
		data.positionRnd = XMFLOAT3(0.4, 0, 0.4);
		data.direction = XMFLOAT3(0, 1, 0);
		data.directionRnd = XMFLOAT3(90, 90, 90);
		data.speed = 0.25f;
		data.speedRnd = 1;
		data.accel = 0.93;
		data.size = XMFLOAT2(0.4, 0.4);
		data.sizeRnd = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(1, 1);
		float color = 1.f;
		data.color = XMFLOAT4(color, color, color, 1);
		data.deltaColor = XMFLOAT4(0, 0, 0, 0);
		data.gravity = 0.003f;

        VFX::Start(data);
    }
}