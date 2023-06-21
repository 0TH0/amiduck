#include "EnemyRed.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Engine/Astar.h"
#include "Engine/Model.h"
#include "Stage.h"

static XMFLOAT3 trans;

//コンストラクタ
EnemyRed::EnemyRed(GameObject* parent)
    :GameObject(parent, "EnemyRed"),hModel_(-1)
{
}

//デストラクタ
EnemyRed::~EnemyRed()
{
}

void EnemyRed::Initialize()
{
    hModel_ = Model::Load("Model\\fire\\fireBall.fbx");
    transform_.position_ = { 0, 1.5f, 10.f };
    
    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.75f);
    AddCollider(collision);
}

void EnemyRed::Update()
{
    Stage* pStage = (Stage*)FindObject("Stage");

    for (int x = 0; x < STAGE_SIZE_X; x++)
    {
        for (int z = 0; z < STAGE_SIZE_Z; z++)
        {
            AI_.SetMapType(pStage->GetStageType(x, z), x, z);
        }
    }


    transform_.rotate_.y += 5;
    Action();
}

void EnemyRed::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void EnemyRed::Release()
{
}

static XMVECTOR v;

void EnemyRed::Action()
{
    Player* pPlayer = (Player*)FindObject("Player");
    
    if (CanMove_)
    {
        if (totalCell >= 0)
        {
            v = { (float)AI_.GetToGoalCell(totalCell).x, 1.5f, (float)AI_.GetToGoalCell(totalCell).z, 0 };

            XMStoreFloat3(&transform_.position_, XMVectorLerp(XMLoadFloat3(&transform_.position_), v, 0.2f));

            //transform_.position_ = VectorToFloat3(v);
        }
    }

    //if (transform_.position_.x == VectorToFloat3(v).x &&
    //    transform_.position_.z == VectorToFloat3(v).z)
    //{

    //}

    //何フレーム毎に進むか
    int frame = 7;

    if (count_ > frame)
    {
        int PlayerPosX = (int)pPlayer->GetPosition().x;
        int PlayerPosZ = (int)pPlayer->GetPosition().z;
        trans = pPlayer->GetPosition();

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