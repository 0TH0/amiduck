#pragma once
#include "EnemyBase.h"

class EnemyBlue : public EnemyBase
{
    int dist_; //�v���C���[�Ƃ̋���
    bool IsPlayerNear_;
public:
    //�R���X�g���N�^
    EnemyBlue(GameObject* parent);

    //�f�X�g���N�^
    ~EnemyBlue();

    void Action() override;
    void InitBase() override;
    void ChangeColor() override;
    void ReleaseBase() override;
};