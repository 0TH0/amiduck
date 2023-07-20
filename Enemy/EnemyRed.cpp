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
    //�G�t�F�N�g
    EnemyEffect::EnemyEffect(transform_.position_, RED);

    Move();

    //�v���C���[�̈ʒu���l�̌ܓ�
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
