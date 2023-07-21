#include "EnemyBase.h"
#include "../Engine/Collider.h"
#include "../Engine/Model.h"

namespace
{
    static const int ROTATE_SPEED = 5;      //回転速度
    static const float DIF_GOAL = 0.3f;     //目的地までの誤差調整
    static const float POSY = 1.5f;         //Y座標
    static const float LERP = 0.2f;         //補間する値
    static const float CENTER = 0.5f;       //当たり判定サイズ
}

EnemyBase::EnemyBase(GameObject* parent, std::string name)
    : GameObject(parent, name), hModel_(-1),frameMove_(7),frameCount_(0),
      AI_(),CanMove_(false),totalCell_(0),v_(),pPlayer_(nullptr)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize()
{
    hModel_ = Model::Load("Model\\fire.fbx");

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(ZERO, ZERO, ZERO), CENTER);
    AddCollider(collision);

    //初期化
    InitBase();
}

void EnemyBase::Update()
{
    pPlayer_ = (Player*)FindObject("Player");
    Stage* pStage = (Stage*)FindObject("Stage");

    //回転
    transform_.rotate_.y += ROTATE_SPEED;

    //現在のステージ情報をセット
    for (int x = ZERO; x < STAGE_SIZE_X; x++)
    {
        for (int z = ZERO; z < STAGE_SIZE_Z; z++)
        {
            AI_.SetMapType(pStage->GetStageType(x, z), x, z);
        }
    }

    //各行動
    Action();
}

void EnemyBase::Draw()
{
    Model::SetTransform(hModel_, transform_);
    //各色変更
    ChangeColor();
    Model::Draw(hModel_);
}

void EnemyBase::Release()
{
    ReleaseBase();
}

void EnemyBase::Move()
{
    //目的地に着いていない場合
    if (CanMove_ && totalCell_ >= ZERO)
    {
        //目的地までのベクトル
        v_ = { (float)AI_.GetToGoalCell(totalCell_).x + DIF_GOAL, POSY, (float)AI_.GetToGoalCell(totalCell_).z + DIF_GOAL, 0 };

        //線形補間
        transform_.position_ = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&transform_.position_), v_, LERP));
    }
}

void EnemyBase::Search(CELL goal)
{
    //フレームがフレームカウントを超えたら
    if (frameCount_ > frameMove_)
    {
        //プレイヤーを探索
        if (AI_.Search({ (int)transform_.position_.x, (int)transform_.position_.z }, goal))
        {
            totalCell_ = AI_.GetToGoalTotalCell();
            CanMove_ = true;
        }
        frameCount_ = 0;
    }
    frameCount_++;
}