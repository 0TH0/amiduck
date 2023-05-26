#include "EnemyMob.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Engine/Astar.h"
#include "Engine/Math.h"
#include "Engine/Model.h"
#include "Stage.h"

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
    hModel_ = Model::Load("Model\\fire\\fireball.fbx");
    transform_.position_ = { 0, 1.5f, 10.f };
    //transform_.scale_ = XMFLOAT3(2.f, 2.f, 2.f);

    //csv読み込み
    //AI_.CsvLoad("Csv\\map4.csv");
}

void EnemyMob::Update()
{
    //Stage* pStage = (Stage*)FindObject("Stage");

    //for (int x = 0; x < STAGE_SIZE_X; x++)
    //{
    //    for (int z = 0; z < STAGE_SIZE_Z; z++)
    //    {
    //        AI_.mapTypeLoad(pStage->GetStageType(x, z));
    //    }
    //}

    transform_.rotate_.y += 5;
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
            XMVECTOR v = { (float)AI_.GetToGoalCell(totalCell).x, 1.5f, (float)AI_.GetToGoalCell(totalCell).z, 0 };

            XMStoreFloat3(&transform_.position_, XMVectorLerp(XMLoadFloat3(&transform_.position_), v, 1.2f));

            transform_.position_ = Math::VectorToFloat3(v);
        }
    }

    //何フレーム毎に進むか
    int frame = 3;

    if (count_ > frame)
    {
        int PlayerPosX = (int)pPlayer->GetPosition().x;
        int PlayerPosZ = (int)pPlayer->GetPosition().z;

        //プレイヤーを探索
        if (AI_.Search({ (int)transform_.position_.x, (int)transform_.position_.z }, { PlayerPosX, PlayerPosZ }))
        {
            totalCell = AI_.GetToGoalTotalCell();
            CanMove_ = true;
        }

        count_ = 0;
    }
    count_++;
}