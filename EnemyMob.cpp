#include "EnemyMob.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Engine/Astar.h"
#include "Engine/Math.h"
#include "Engine/Model.h"

//コンストラクタ
EnemyMob::EnemyMob(GameObject* parent)
    :GameObject(parent, "EnemyMob"),hModel_(-1)
{
}

//デストラクタ
EnemyMob::~EnemyMob()
{
}

void EnemyMob::Initialize()
{
    hModel_ = Model::Load("Model\\star_white.fbx");
    transform_.position_ = { 0, 1, 10.f };
    transform_.scale_ = XMFLOAT3(0.1f, 0.1f, 0.1f);
}

void EnemyMob::Update()
{
    transform_.rotate_.y+=10;
    Action();
}

void EnemyMob::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void EnemyMob::Release()
{
}

void EnemyMob::Action()
{
    Player* pPlayer = (Player*)FindObject("Player");

    if (CanMove_)
    {
        if (totalCell >= 0)
        {
            XMVECTOR v = { (float)AI_.GetToGoalCell(totalCell).x, 1.5f, (float)AI_.GetToGoalCell(totalCell).z,0 };

            XMStoreFloat3(&transform_.position_, XMVectorLerp(XMLoadFloat3(&transform_.position_), v, 0.2f));

            transform_.position_ = Math::VectorToFloat3(v);
        }
    }

    //何フレーム毎に進むか
    int frame = 5;

    if (count_ > frame)
    {
        int x = (int)pPlayer->GetPosition().x;
        int z = (int)pPlayer->GetPosition().z;

        //プレイヤーを探索
        if (AI_.Search("Csv\\map4.csv", { (int)transform_.position_.x, (int)transform_.position_.z }, { x, z }))
        {
            totalCell = AI_.GetToGoalTotalCell();
            CanMove_ = true;
        }

        count_ = 0;
    }
    count_++;
}