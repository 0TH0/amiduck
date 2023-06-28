#include "EnemyGreen.h"

EnemyGreen::EnemyGreen(GameObject* parent)
    :EnemyBase(parent, "EnemyGreen"),randX_(0),randZ_(0)
{
}

EnemyGreen::~EnemyGreen()
{
}

void EnemyGreen::Action()
{
    EnemyEffect::EnemyEffectGreen(transform_.position_);
    if (CanMove_)
    {
        if (totalCell >= 0)
        {
            v = { (float)AI_.GetToGoalCell(totalCell).x + 0.4f, 1.5f, (float)AI_.GetToGoalCell(totalCell).z + 0.4f, 0 };

            XMStoreFloat3(&transform_.position_, XMVectorLerp(XMLoadFloat3(&transform_.position_), v, 0.2f));
        }
    }

    if (!AI_.GetExistMinNode())
    {
        randX_ = rand() % STAGE_SIZE_X + 1;
        randZ_ = rand() % STAGE_SIZE_Z + 1;
    }

    if (count_ > frame)
    {
        int PlayerPosX = (int)pPlayer_->GetPosition().x;
        int PlayerPosZ = (int)pPlayer_->GetPosition().z;
        //ÉvÉåÉCÉÑÅ[ÇíTçı
        if (AI_.Search({ (int)transform_.position_.x, (int)transform_.position_.z }, { randX_, randZ_}))
        {
            totalCell = AI_.GetToGoalTotalCell();
            CanMove_ = true;
        }

        count_ = 0;
    }
    count_++;
}

void EnemyGreen::InitBase()
{
}

void EnemyGreen::ChangeColor()
{
    Model::SetColor(hModel_, { 0,1,0,1 });
}

void EnemyGreen::ReleaseBase()
{
}
