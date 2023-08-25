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
    Move();

    //プレイヤーの位置を四捨五入
    int PlayerPosX = round(pPlayer_->GetPosition().x);
    int PlayerPosZ = round(pPlayer_->GetPosition().z);

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
