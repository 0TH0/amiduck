#pragma once
#include "EnemyBase.h"

class EnemyWhite : public EnemyBase
{
public:
    //コンストラクタ
    EnemyWhite(GameObject* parent);

    //デストラクタ
    ~EnemyWhite();

    void Action() override;
    void InitBase() override;
    void ChangeColor() override;
    void ReleaseBase() override;
};