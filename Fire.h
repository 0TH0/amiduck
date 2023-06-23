#pragma once
#include "EnemyBase.h"

class Fire : public EnemyBase
{
    Transform trans_;
public:
    //�R���X�g���N�^
    Fire(GameObject* parent);

    //�f�X�g���N�^
    ~Fire();

    void Action() override;
    void InitBase() override;
    void ChangeColor() override;
    void ReleaseBase() override;
};