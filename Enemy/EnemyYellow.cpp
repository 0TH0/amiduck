#include "EnemyYellow.h"

EnemyYellow::EnemyYellow(GameObject* parent)
    :EnemyBase(parent, "EnemyYellow"), dist_(30), IsPlayerNear_(false)
{
}

EnemyYellow::~EnemyYellow()
{
}

void EnemyYellow::Action()
{
    //�v���C���[�ƓG�̋�����30�ȉ��Ȃ�
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

void EnemyYellow::InitBase()
{
    hModel_ = Model::Load("Model/Player/duck_yellow.fbx");
}

void EnemyYellow::ChangeColor()
{
    Model::SetColor(hModel_, BLUE);
}

void EnemyYellow::ReleaseBase()
{
}
