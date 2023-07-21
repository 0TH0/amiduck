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
    //エフェクト
    EnemyEffect::EnemyEffect(transform_.position_, BLUE);

    //プレイヤーと青の距離が30以下なら
    IsPlayerNear_ = (CalcDist(GetPosition(), pPlayer_->GetPosition()) <= dist_);
    if (IsPlayerNear_)
    {
        Move();
    }

    //プレイヤーの位置を四捨五入
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
