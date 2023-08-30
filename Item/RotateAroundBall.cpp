#include "RotateAroundBall.h"
#include "../Stage/Stage.h"
#include "../Scene/PlayScene.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "../Engine/SphereCollider.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Color.h"
#include "../Player/Player.h"
#include "../Manager/AudioManager.h"

namespace
{
    static const int   MAX_TIME = 200;//何秒回転するか
    static const float SPEED = 10.f;  //回転速度
    static const float DIS  = 7.f;    //中心からの距離
    static const float RADIUS = 1.5f;  //中心
}

//コンストラクタ
RotateAroundBall::RotateAroundBall(GameObject* parent)
    : GameObject(parent, "RotateAroundBall"),hModel_(-1),pLine_()
{
}

//デストラクタ
RotateAroundBall::~RotateAroundBall()
{
}

//初期化
void RotateAroundBall::Initialize()
{
    hModel_ = Model::Load("Model\\fire.fbx");
    assert(hModel_ >= ZERO);

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), RADIUS);
    AddCollider(collision);

    pLine_ = new PolyLine;
    pLine_->Load("Image\\line_white.png");
    assert(pLine_ != nullptr);

    Player* pPlayer = (Player*)FindObject("Player");
    transform_.position_ = pPlayer->GetPosition();
    transform_.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5);

    //アウトライン使用
    Model::SetOutLineDrawFlag(hModel_, true);
}

//更新
void RotateAroundBall::Update()
{
    Player* pPlayer = (Player*)FindObject("Player");

    //プレイヤーの周りを回る
    transform_.position_ = Transform::RotateAround(pPlayer->GetPosition(), DIS, SPEED);

    time_++;

    //一定時間経ったら消える
    if (time_ >= MAX_TIME)
    {
        KillMe();
    }
    pLine_->AddPosition(transform_.position_);
}

//描画
void RotateAroundBall::Draw()
{
    pLine_->SetColor(BLUE);
    pLine_->Draw();
    Model::SetColor(hModel_, BLUE);
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void RotateAroundBall::Release()
{
}

void RotateAroundBall::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "EnemyBlue" ||
        pTarget->GetObjectName() == "EnemyGreen" ||
        pTarget->GetObjectName() == "EnemyRed")
    {
        AudioManager::HitAudio();
        pTarget->KillMe();
    }
}