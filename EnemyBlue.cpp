#include "EnemyBlue.h"

EnemyBlue::EnemyBlue(GameObject* parent)
    :EnemyBase(parent, "EnemyBlue"), dist_(15)
{
}

EnemyBlue::~EnemyBlue()
{
}

void EnemyBlue::Action()
{
    EnemyEffect::EnemyEffectBlue(transform_.position_);
    //�v���C���[�Ɛ̋�����15�ȉ��Ȃ�
    bool isPlayerNear = (CalcDist(GetPosition(), pPlayer_->GetPosition()) <= dist_);
    if (CanMove_ && isPlayerNear)
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
        //�v���C���[��T��
        if (AI_.Search({ (int)transform_.position_.x, (int)transform_.position_.z }, { PlayerPosX, PlayerPosZ }))
        {
            totalCell = AI_.GetToGoalTotalCell();
            CanMove_ = true;
        }

        count_ = 0;
    }
    count_++;
}

void EnemyBlue::InitBase()
{
}

void EnemyBlue::ChangeColor()
{
    Model::SetColor(hModel_, { 0,0,1,1 });
}

void EnemyBlue::ReleaseBase()
{
}
