#include "EnemyEffect.h"
#include "../Engine/VFX.h"

namespace EnemyEffect
{
	void EnemyEffectRed(XMFLOAT3 pos)
	{
        EmitterData data;
        data.textureFileName = "Image\\Cloud.png";
        data.position = pos;
        data.positionRnd = XMFLOAT3(0.1, 0, 0.1);
        data.delay = 0;
        data.number = 1;
        data.lifeTime = 60;
        //data.gravity = -0.002f;
        data.direction = XMFLOAT3(0, 1, 0);
        data.directionRnd = XMFLOAT3(0, 0, 0);
        data.speed = 0.01f;
        data.speedRnd = 0.0;
        data.size = XMFLOAT2(1.5, 1.5);
        data.sizeRnd = XMFLOAT2(0.4, 0.4);
        data.scale = XMFLOAT2(1.01, 1.01);
        data.color = XMFLOAT4(1, 1, 0, 1);
        data.deltaColor = XMFLOAT4(0, -0.03, 0, -0.02);
        VFX::Start(data);
	}
    void EnemyEffectBlue(XMFLOAT3 pos)
    {
        EmitterData data;
        data.textureFileName = "Image\\Cloud.png";
        data.position = pos;
        data.positionRnd = XMFLOAT3(0.1, 0, 0.1);
        data.delay = 0;
        data.number = 1;
        data.lifeTime = 60;
        //data.gravity = -0.002f;
        data.direction = XMFLOAT3(0, 1, 0);
        data.directionRnd = XMFLOAT3(0, 0, 0);
        data.speed = 0.01f;
        data.speedRnd = 0.0;
        data.size = XMFLOAT2(1.5, 1.5);
        data.sizeRnd = XMFLOAT2(0.4, 0.4);
        data.scale = XMFLOAT2(1.01, 1.01);
        data.color = XMFLOAT4(0, 0, 1, 1);
        data.deltaColor = XMFLOAT4(0, -0.03, 0, -0.02);
        VFX::Start(data);
    }
    void EnemyEffectGreen(XMFLOAT3 pos)
    {
        EmitterData data;
        data.textureFileName = "Image\\Cloud.png";
        data.position = pos;
        data.positionRnd = XMFLOAT3(0.1, 0, 0.1);
        data.delay = 0;
        data.number = 1;
        data.lifeTime = 60;
        //data.gravity = -0.002f;
        data.direction = XMFLOAT3(0, 1, 0);
        data.directionRnd = XMFLOAT3(0, 0, 0);
        data.speed = 0.01f;
        data.speedRnd = 0.0;
        data.size = XMFLOAT2(1.5, 1.5);
        data.sizeRnd = XMFLOAT2(0.4, 0.4);
        data.scale = XMFLOAT2(1.01, 1.01);
        data.color = XMFLOAT4(0, 1, 0, 1);
        data.deltaColor = XMFLOAT4(0, -0.03, 0, -0.02);
        VFX::Start(data);
    }
}