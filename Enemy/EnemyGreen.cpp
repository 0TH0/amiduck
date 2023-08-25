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
    Move();

    //最短ノードが空か(なかったら目的地についてる)
    if (!AI_.GetExistMinNode())
    {
        randX_ = rand() % STAGE_SIZE_X + 1;
        randZ_ = rand() % STAGE_SIZE_Z + 1;
    }

    Search({ randX_, randZ_ });
}

void EnemyGreen::InitBase()
{
}

void EnemyGreen::ChangeColor()
{
    Model::SetColor(hModel_, GREEN);
}

void EnemyGreen::ReleaseBase()
{
}
