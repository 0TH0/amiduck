#pragma once
#include "EnemyBase.h"

class EnemyYellow : public EnemyBase
{
    int dist_; //�v���C���[�Ƃ̋���
    bool IsPlayerNear_;
public:
    //�R���X�g���N�^
    EnemyYellow(GameObject* parent);

    //�f�X�g���N�^
    ~EnemyYellow();

    void Action() override;
    void InitBase() override;
    void ChangeColor() override;
    void ReleaseBase() override;
};