#include "Boss2.h"
#include "Boss.h"
#include "Player.h"

#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"

//コンストラクタ
Boss2::Boss2(GameObject* parent)
    :GameObject(parent, "Boss2"), hModel_(-1),
    SPEED(0.04),RotateSpeed(6.0f),
    IsJump(false),time(0)
{
}

//デストラクタ
Boss2::~Boss2()
{
}

//初期化
void Boss2::Initialize()
{
    hModel_ = Model::Load("Boss.fbx");
    assert(hModel_ >= 0);

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), 2.0f);
    AddCollider(collision);

    transform_.scale_ = XMFLOAT3(4.0f, 4.0f, 4.0f);
    transform_.rotate_.y = 180.0f;

    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);
}

void Boss2::Update()
{
    //// 1フレーム前の座標
    //XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);

    ////時間
    //time += 0.005f;

    ////移動
    //if (time > 1.0f)
    //{
    //    transform_.position_.x -= SPEED;
    //}
    //if (time > 2.0f)
    //{
    //    time = 0;
    //}
    //if(time < 1.0f)
    //{
    //    transform_.position_.x += SPEED;
    //}

    ////回転
    //transform_.rotate_.z += RotateSpeed;

    ////重力
    //GRAVITY = 0.05f;
    //move_.y = -GRAVITY;
    //transform_.position_.y += move_.y;

    ////////////////////壁との衝突判定///////////////////////
    //float objX = transform_.position_.x;
    //float objY = transform_.position_.y;

    ////壁の判定(上)
    //if (pStage->IsWall((int)objX, (int)(objY - 1.5f)) || pStage->IsWallX((int)objX, (int)(objY - 1.5f)))
    //{
    //    transform_.position_.y = (float)(int)(transform_.position_.y) + 0.4f;
    //    IsJump = 0;
    //}

    ////壁の判定(右)
    //if (pStage->IsWall((int)(objX + 0.2f), (int)objY))
    //{
    //    transform_.position_.x = (float)(int)(transform_.position_.x) - 0.4f;
    //    SPEED *= -1;
    //    transform_.rotate_.z -= RotateSpeed;
    //}

    ////壁の判定(左)
    //if (pStage->IsWall((int)(objX - 0.2f), (int)objY))
    //{
    //    transform_.position_.x = (float)(int)(transform_.position_.x) + 0.4f;
    //    SPEED *= -1;
    //    transform_.rotate_.z -= RotateSpeed; 
    //}
}

void Boss2::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Boss2::Release()
{
}

void Boss2::OnCollision(GameObject* pTarget)
{
}