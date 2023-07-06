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
    EnemyEffect::EnemyEffect(transform_.position_, BLUE);
    //ƒvƒŒƒCƒ„[‚ÆÂ‚Ì‹——£‚ª30ˆÈ‰º‚È‚ç
    IsPlayerNear_ = (CalcDist(GetPosition(), pPlayer_->GetPosition()) <= dist_);

    if (IsPlayerNear_)
    {
        Move();
    }

    int PlayerPosX = (int)pPlayer_->GetPosition().x;
    int PlayerPosZ = (int)pPlayer_->GetPosition().z;

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
