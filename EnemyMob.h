#pragma once
#include "CharacterBase.h"
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Astar.h"

//◆◆◆を管理するクラス
class EnemyMob : public GameObject
{
    int EnemyTime_;
    XMFLOAT3 playerPos_;
    int count_;
    Astar AI_;
    bool CanMove_;
    int totalCell;
    int hModel_;
public:
    //コンストラクタ
    EnemyMob(GameObject* parent);

    //デストラクタ
    ~EnemyMob();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void Action();

    XMVECTOR SmoothStep(XMVECTOR V0, XMVECTOR V1, float t)
    {
        t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
        t = t * t * (3.f - 2.f * t);
        return XMVectorLerp(V0, V1, t);
    }
};