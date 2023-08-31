#pragma once
#include "EnemyBase.h"

class EnemyYellow : public EnemyBase
{
    int dist_; //プレイヤーとの距離
    bool IsPlayerNear_;
public:
    //コンストラクタ
    EnemyYellow(GameObject* parent);

    //デストラクタ
    ~EnemyYellow();

    void Action() override;
    void InitBase() override;
    void ChangeColor() override;
    void ReleaseBase() override;
};