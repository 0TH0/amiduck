#include "EnemyRed.h"

EnemyRed::EnemyRed(GameObject* parent)
    :EnemyBase(parent, "EnemyRed")
{
}

EnemyRed::~EnemyRed()
{
}

void EnemyRed::Action()
{
    //エフェクト
    EnemyEffect::EnemyEffect(transform_.position_, RED);

    Move();

    int PlayerPosX = (int)pPlayer_->GetPosition().x;
    int PlayerPosZ = (int)pPlayer_->GetPosition().z;

    Search({ PlayerPosX, PlayerPosZ });
}

void EnemyRed::InitBase()
{
}

void EnemyRed::ChangeColor()
{
    Model::SetColor(hModel_, RED);
}

void EnemyRed::ReleaseBase()
{
}
