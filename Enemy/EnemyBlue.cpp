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
    hModel_ = Model::Load("Model/Player/duck_yellow.fbx");
}

void EnemyBlue::ChangeColor()
{
    Model::SetColor(hModel_, BLUE);
}

void EnemyBlue::ReleaseBase()
{
}
