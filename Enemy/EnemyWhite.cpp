#include "EnemyWhite.h"

EnemyWhite::EnemyWhite(GameObject* parent)
    :EnemyBase(parent, "EnemyWhite")
{
}

EnemyWhite::~EnemyWhite()
{
}

void EnemyWhite::Action()
{
    Move();

    //�v���C���[�̈ʒu���l�̌ܓ�
    int PlayerPosX = round(pPlayer_->GetPosition().x);
    int PlayerPosZ = round(pPlayer_->GetPosition().z);

    Search({ PlayerPosX, PlayerPosZ });
}

void EnemyWhite::InitBase()
{
    hModel_ = Model::Load("Model/Player/duck_white.fbx");
}

void EnemyWhite::ChangeColor()
{
    Model::SetColor(hModel_, RED);
}

void EnemyWhite::ReleaseBase()
{
}
