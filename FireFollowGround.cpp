#include "FireFollowGround.h"
#include "Stage.h"
#include "Scene/PlayScene.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Color.h"
#include "Player.h"

namespace
{
    static const int TIMEMAX = 200;
    static const float SPEED = 10.f;
    static const float DIS  = 7.f;
}

//コンストラクタ
FireFollowGround::FireFollowGround(GameObject* parent)
    : GameObject(parent, "FireFollowGround"),hModel_(-1),pLine_()
{
}

//デストラクタ
FireFollowGround::~FireFollowGround()
{
}

//初期化
void FireFollowGround::Initialize()
{
    hModel_ = Model::Load("Model\\fire_blue.fbx");
    assert(hModel_ >= 0);

    //位置
    transform_.scale_ = XMFLOAT3(0.75, 0.75, 0.75);

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.75f);
    AddCollider(collision);

    pLine_ = new PolyLine;
    pLine_->Load("Image\\line_white.png");
    assert(pLine_ != nullptr);

    Player* pPlayer = (Player*)FindObject("Player");
    transform_.position_ = pPlayer->GetPosition();

}

//更新
void FireFollowGround::Update()
{
    Player* pPlayer = (Player*)FindObject("Player");
    transform_.position_ = Transform::RotateAround(pPlayer->GetPosition(), DIS, SPEED);
    time_++;

    if (time_ >= TIMEMAX)
    {
        KillMe();
    }

    pLine_->AddPosition(transform_.position_);
}

//描画
void FireFollowGround::Draw()
{
    pLine_->SetColor(BLUE);
    pLine_->Draw();
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void FireFollowGround::Release()
{
}

void FireFollowGround::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "EnemyBlue" ||
        pTarget->GetObjectName() == "EnemyGreen" ||
        pTarget->GetObjectName() == "EnemyRed" ||
        pTarget->GetObjectName() == "Fire")
    {
        pTarget->KillMe();
    }
}
