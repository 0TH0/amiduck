#pragma once
#include "EnemyBase.h"

class EnemyWhite : public EnemyBase
{
public:
    //�R���X�g���N�^
    EnemyWhite(GameObject* parent);

    //�f�X�g���N�^
    ~EnemyWhite();

    void Action() override;
    void InitBase() override;
    void ChangeColor() override;
    void ReleaseBase() override;
};