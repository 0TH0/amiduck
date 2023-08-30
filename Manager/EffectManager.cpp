#include "EffectManager.h"
#include "../Engine/VFX.h"

namespace EffectManager
{
    void ElectricEffect(XMFLOAT3 pos)
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

    //敵のエフェクト
    void EnemyEffect(XMFLOAT3 pos, XMFLOAT4 color)
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
        data.color = color;
        data.deltaColor = XMFLOAT4(0, -0.03, 0, -0.02);
        VFX::Start(data);
    }

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

    void StarEffect(XMFLOAT3 pos)
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
    void RiverEffect(XMFLOAT3 pos)
    {
        EmitterData data;

        data.textureFileName = "Particle/water.png";
        data.position = XMFLOAT3(pos);
        data.delay = 1;
        data.number = 3;
        data.lifeTime = 150;
        data.direction = XMFLOAT3(0, 0, -1);
        data.directionRnd = XMFLOAT3(0, 0, 0);
        data.gravity = 0.005;
        data.speed = 0.1f;
        data.accel = 0.98;
        data.speedRnd = 0.5;
        data.size = XMFLOAT2(1, 1);
        data.speedRnd = 1;
        data.scale = XMFLOAT2(1.02, 1.02);
        data.color = XMFLOAT4(1, 1, 1, 0.1);
        VFX::Start(data);

        //水滴
        data.textureFileName = "Particle/buble.png";
        data.position = XMFLOAT3(pos);
        data.positionRnd = XMFLOAT3(0.5, 0, 0);
        data.delay = 1;
        data.number = 3;
        data.lifeTime = 50;
        data.direction = XMFLOAT3(0, 0, -1);
        data.directionRnd = XMFLOAT3(0, 20, 0);
        data.gravity = 0.005;
        data.speed = 0.1f;
        data.accel = 0.98;
        data.speedRnd = 0.0;
        data.size = XMFLOAT2(0.3, 0.3);
        data.speedRnd = 0;
        data.scale = XMFLOAT2(0.98, 0.98);
        data.color = XMFLOAT4(1, 1, 1, 1);
        VFX::Start(data);
    }
}