#include "Enemy.h"
#include "Player.h"
#include "Pipe_base.h"

#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"

//コンストラクタ
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy"), hModel_(-1),
    SPEED(0.02)
{
}

//デストラクタ
Enemy::~Enemy()
{
}

//初期化
void Enemy::Initialize()
{
    hModel_ = Model::Load("Enemy.fbx");
    assert(hModel_ >= 0);

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0.0f, 0.3f, 0.0f), 0.3f);
    AddCollider(collision);

    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);
}

void Enemy::Update()
{
   // // 1フレーム前の座標
   // XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);

   // //移動
   // transform_.position_.x += SPEED;

   // //重力
   // GRAVITY = 0.075f;
   // move_.y = -GRAVITY;
   // transform_.position_.y += move_.y;

   // //////////////////壁との衝突判定///////////////////////
   // float objX = transform_.position_.x;
   // float objY = transform_.position_.y;

   // //壁の判定(上)
   // if (pStage->IsWall((int)objX, (int)(objY - 0.2f)) || pStage->IsWallX((int)objX, (int)(objY - 0.2f)))
   // {
   //     transform_.position_.y = (float)(int)(transform_.position_.y) + 0.2f;
   // }

   // //壁の判定(下)
   // if (pStage->IsWall((int)objX, (int)(objY + 0.2f)) || pStage->IsWallX((int)objX, (int)(objY + 0.2f)))
   // {
   //     transform_.position_.y = (float)(int)(transform_.position_.y + 0.5f) - 0.2f;
   // }

   // //壁の判定(右)
   // if (pStage->IsWall((int)(objX + 0.2f), (int)objY))
   // {
   //     transform_.position_.x = (float)(int)(transform_.position_.x + 0.5f) - 0.2f;
   //     SPEED *= -1;
   // }

   // //壁の判定(左)
   // if (pStage->IsWall((int)(objX - 0.2f), (int)objY))
   // {
   //     transform_.position_.x = (float)(int)(transform_.position_.x) + 0.2f;
   //     SPEED *= -1;
   // }

   // //////////////////土管との衝突判定///////////////////////
   // // 
   // //土管の判定(上)
   // if (pStage->IsPipe((int)objX, (int)(objY - 0.2f)))
   // {
   //     transform_.position_.y = (float)(int)(transform_.position_.y) + 0.2f;
   // }

   // //土管の判定(下)
   // if (pStage->IsPipe((int)objX, (int)(objY + 0.2f)))
   // {
   //     transform_.position_.y = (float)(int)(transform_.position_.y + 0.5f) - 0.4f;
   // }

   // //土管の判定(右)
   // if (pStage->IsPipe((int)(objX + 0.4f), (int)objY))
   // {
   //     transform_.position_.x = (float)(int)(transform_.position_.x + 0.5f) - 0.4f;
   //     SPEED *= -1;
   // }

   // //土管の判定(左)
   // if (pStage->IsPipe((int)(objX - 0.4f), (int)objY))
   // {
   //     transform_.position_.x = (float)(int)(transform_.position_.x) + 0.4f;
   //     SPEED *= -1;
   // }

   // ///////////// 敵の向き /////////////

   ////現在の位置のベクトル
   // XMVECTOR nowPosition = XMLoadFloat3(&transform_.position_);

   // //今回位置のベクトル
   // XMVECTOR nowMove = nowPosition - prevPosition;

   // //移動べクトル
   // XMVECTOR Length = XMVector3Length(nowMove);

   // //0.1以上の時は実行しない
   // if (XMVectorGetX(Length) > 0.01)
   // {
   //     //角度を求めるのに長さを1にする（正規化）
   //     nowMove = XMVector3Normalize(nowMove);

   //     //基準となる向きのベクトル
   //     XMVECTOR front = { 0, 0, 1, 0 };

   //     //frontとmoveの外積を求める
   //     XMVECTOR vecDot = XMVector3Dot(front, nowMove);
   //     float dot = XMVectorGetX(vecDot);

   //     //向いてる角度を求める(ラジアン)
   //     float angle = acos(dot);

   //     //frontとmoveの外積を求める
   //     XMVECTOR cross = XMVector3Cross(front, nowMove);

   //     //外積がマイナスだと下向き
   //     if (XMVectorGetY(cross) < 0)
   //     {
   //         angle *= -1;
   //     }

   //     //その角度回転させる
   //     transform_.rotate_.y = angle * 180.0f / 3.14f;
   // }
}

void Enemy::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Enemy::Release()
{
}

void Enemy::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Player")
    {
        KillMe();
    }
}