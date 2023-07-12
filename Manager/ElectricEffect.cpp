#include "ElectricEffect.h"
#include "../Engine/VFX.h"

namespace ElectricEffect
{
    void ElectricEffect::ElectricEffect(XMFLOAT3 pos)
    {
        EmitterData data;
        data.textureFileName = "Image\\ele.png";
        data.position = pos;
        data.position.y += 5;
        data.positionRnd = XMFLOAT3(0.1, 0, 0.1);
        data.delay = 0;
        data.number = 2;
        data.lifeTime = 60;
        data.gravity = 0;
        data.direction = XMFLOAT3(0, -1, 0);
        data.directionRnd = XMFLOAT3(0, 0, 0);
        data.speed = 0.01f;
        data.speedRnd = 0.0;
        data.size = XMFLOAT2(10, 10);
        data.sizeRnd = XMFLOAT2(0, 0);
        data.scale = XMFLOAT2(1.0, 1.0);
        data.color = { 1,1,1,1 };
        data.deltaColor = XMFLOAT4(0, -0.03, 0, -0.02);
        VFX::Start(data);
    }
}