#pragma once
#include "EnemyBase.h"

class EnemyGreen : public EnemyBase
{
    int randX_; //�����_��X
    int randZ_; //�����_��Z
public:
    //�R���X�g���N�^
    EnemyGreen(GameObject* parent);

    //�f�X�g���N�^
    ~EnemyGreen();

    void Action() override;
    void InitBase() override;
    void ChangeColor() override;
    void ReleaseBase() override;
};