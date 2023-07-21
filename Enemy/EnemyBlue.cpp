#include "EnemyBlue.h"

EnemyBlue::EnemyBlue(GameObject* parent)
    :EnemyBase(parent, "EnemyBlue"), dist_(30), IsPlayerNear_(false)
{
}

EnemyBlue::~EnemyBlue()
{
}

void EnemyBlue::Action()
{
    //�G�t�F�N�g
    EnemyEffect::EnemyEffect(transform_.position_, BLUE);

    //�v���C���[�Ɛ̋�����30�ȉ��Ȃ�
    IsPlayerNear_ = (CalcDist(GetPosition(), pPlayer_->GetPosition()) <= dist_);
    if (IsPlayerNear_)
    {
        Move();
    }

    //�v���C���[�̈ʒu���l�̌ܓ�
    int PlayerPosX = round(pPlayer_->GetPosition().x);
    int PlayerPosZ = round(pPlayer_->GetPosition().z);
    
    Search({ PlayerPosX, PlayerPosZ });
}

void EnemyBlue::InitBase()
{
}

void EnemyBlue::ChangeColor()
{
    Model::SetColor(hModel_, BLUE);
}

void EnemyBlue::ReleaseBase()
{
}
