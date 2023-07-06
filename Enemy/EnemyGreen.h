#pragma once
#include "EnemyBase.h"

class EnemyGreen : public EnemyBase
{
    int randX_; //ランダムX
    int randZ_; //ランダムZ
public:
    //コンストラクタ
    EnemyGreen(GameObject* parent);

    //デストラクタ
    ~EnemyGreen();

    void Action() override;
    void InitBase() override;
    void ChangeColor() override;
    void ReleaseBase() override;
};