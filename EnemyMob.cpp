#include "EnemyMob.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Engine/Astar.h"
#include "Engine/Math.h"
#include "Engine/Model.h"
#include "Stage.h"

static XMFLOAT3 trans;

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
}

void EnemyMob::Update()
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

void EnemyMob::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void EnemyMob::Release()
{
}

static XMVECTOR v;
void EnemyMob::Action()
{
    Player* pPlayer = (Player*)FindObject("Player");
    XMVECTOR before = XMLoadFloat3(&transform_.position_);

    SmoothStep(before, v, 0.05f);

    if (CanMove_)
    {
        if (totalCell >= 0)
        {
            v = { (float)AI_.GetToGoalCell(totalCell).x, 1.5f, (float)AI_.GetToGoalCell(totalCell).z, 0 };

            transform_.position_ = Math::VectorToFloat3(v);
        }
    }

    //何フレーム毎に進むか
    int frame = 10;

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