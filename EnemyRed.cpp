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
    EnemyEffect::EnemyEffectRed(transform_.position_);

    if (CanMove_)
    {
        if (totalCell >= 0)
        {
            XMVECTOR v = { AI_.GetToGoalCell(totalCell).x, 1.5f, AI_.GetToGoalCell(totalCell).z, 0 };

            XMStoreFloat3(&transform_.position_, XMVectorLerp(XMLoadFloat3(&transform_.position_), v, 0.3f));

            transform_.position_ = VectorToFloat3(v);
        }
    }

    if (count_ > frame)
    {
        int PlayerPosX = (int)pPlayer_->GetPosition().x;
        int PlayerPosZ = (int)pPlayer_->GetPosition().z;
        //ÉvÉåÉCÉÑÅ[ÇíTçı
        if (AI_.Search({ (int)transform_.position_.x, (int)transform_.position_.z }, { PlayerPosX, PlayerPosZ }))
        {
            totalCell = AI_.GetToGoalTotalCell();
            CanMove_ = true;
        }

        count_ = 0;
    }
    count_++;
}

void EnemyRed::InitBase()
{
}

void EnemyRed::ChangeColor()
{
    Model::SetColor(hModel_, { 1,0,0,1 });
}

void EnemyRed::ReleaseBase()
{
}
