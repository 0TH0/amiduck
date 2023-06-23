#include "EnemyBase.h"
#include "Engine/Collider.h"
#include "Engine/Model.h"

EnemyBase::EnemyBase(GameObject* parent, std::string name)
    : GameObject(parent, name), hModel_(-1),frame(7), pPlayer_(),count_(0),
      AI_(),CanMove_(false),totalCell(0),v()
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize()
{
    hModel_ = Model::Load("Model\\fire.fbx");

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.75f);
    AddCollider(collision);

    InitBase();
}

void EnemyBase::Update()
{
    pPlayer_ = (Player*)FindObject("Player");
    Stage* pStage = (Stage*)FindObject("Stage");

    //現在のステージ情報をセット
    for (int x = 0; x < STAGE_SIZE_X; x++)
    {
        for (int z = 0; z < STAGE_SIZE_Z; z++)
        {
            AI_.SetMapType(pStage->GetStageType(x, z), x, z);
        }
    }

    //回転
    transform_.rotate_.y += 5;

    Action();
}

void EnemyBase::Draw()
{
    Model::SetTransform(hModel_, transform_);
    ChangeColor();
    Model::Draw(hModel_);
   
}

void EnemyBase::Release()
{
    ReleaseBase();
}
