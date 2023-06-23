#include "Fire.h"

Fire::Fire(GameObject* parent)
    :EnemyBase(parent, "Fire")
{
}

Fire::~Fire()
{
}

void Fire::Action()
{
    //EnemyEffect::EnemyEeffect(transform_.position_, { 1,1,0,1 });

    if (CanMove_)
    {
        if (totalCell >= 0)
        {
            v = { (float)AI_.GetToGoalCell(totalCell).x + 0.3f, 1.5f, (float)AI_.GetToGoalCell(totalCell).z + +0.3f, 0 };

            transform_.position_ = Transform::RotateAround(trans_.position_, 10.f, 3.f, true);

            XMStoreFloat3(&trans_.position_, XMVectorLerp(XMLoadFloat3(&trans_.position_), v, 0.2f));
        }
    }

    if (count_ > frame)
    {
        int PlayerPosX = (int)pPlayer_->GetPosition().x;
        int PlayerPosZ = (int)pPlayer_->GetPosition().z;
        //ÉvÉåÉCÉÑÅ[ÇíTçı
        if (AI_.Search({ (int)trans_.position_.x, (int)trans_.position_.z }, { PlayerPosX, PlayerPosZ }))
        {
            totalCell = AI_.GetToGoalTotalCell();
            CanMove_ = true;
        }

        count_ = 0;
    }
    count_++;
}

void Fire::InitBase()
{
    transform_.position_ = { 90, 1.5,7 };
    trans_.position_ = transform_.position_;
    frame = 5;
}

void Fire::ChangeColor()
{
    Model::SetColor(hModel_, { 1,1,0,1 });
}

void Fire::ReleaseBase()
{
}
