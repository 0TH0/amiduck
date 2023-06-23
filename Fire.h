#pragma once
#include "EnemyBase.h"

class Fire : public EnemyBase
{
    Transform trans_;
public:
    //コンストラクタ
    Fire(GameObject* parent);

    //デストラクタ
    ~Fire();

    void Action() override;
    void InitBase() override;
    void ChangeColor() override;
    void ReleaseBase() override;
};