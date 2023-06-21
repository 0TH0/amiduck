#include "BombEffect.h"
#include "../Engine/VFX.h"

namespace StageEffect
{
    void PopBridgeEffect(XMFLOAT3 pos)
    {
        EmitterData data;
        data.textureFileName = "Particle\\Cloud.png";
        data.position = pos;
        data.positionRnd = XMFLOAT3(0.1f, 0, 0.1f);
        data.delay = 0;
        data.number = 5;
        data.lifeTime = 60;
        data.direction = XMFLOAT3(0, 1, 0);
        data.directionRnd = XMFLOAT3(0, 0, 0);
        data.speed = 0.01f;
        data.speedRnd = 0.5;
        data.size = XMFLOAT2(2, 2);
        data.sizeRnd = XMFLOAT2(0.4f, 0.4f);
        data.scale = XMFLOAT2(1.03f, 1.02f);
        float color = 0.5;
        data.color = XMFLOAT4(color, color, color, 0.1f);
        VFX::Start(data);
    }
}