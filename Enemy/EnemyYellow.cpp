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
    //プレイヤーと敵の距離が30以下なら
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
