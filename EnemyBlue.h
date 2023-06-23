#pragma once
#include "EnemyBase.h"

class EnemyBlue : public EnemyBase
{
    int dist_; //プレイヤーとの距離
    bool IsPlayerNear_;
public:
    //コンストラクタ
    EnemyBlue(GameObject* parent);

    //デストラクタ
    ~EnemyBlue();

    void Action() override;
    void InitBase() override;
    void ChangeColor() override;
    void ReleaseBase() override;
};