#include "Player.h"
#include "Scene/PlayScene.h"
#include "FireFollowGround.h"
#include "Controller.h"
#include "Enemy.h"
#include "Line.h"
#include "Bomb.h"
#include "Item.h"
#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :CharacterBase(parent, "Player")
{
}

//デストラクタ
Player::~Player()
{
}

void Player::Action()
{
    if (IsSpeedUp_)
    {
        SpeedUpTime_++;
        speed_ = 0.4;
    }
    if (SpeedUpTime_ > 60)
    {
        IsSpeedUp_ = false;
        SpeedUpTime_ = 0;
    }
}

void Player::Command()
{
    //アイテム使用
    if (Input::IsKeyDown(DIK_E) /*&& hasItem_*/)
    {
        Item* pItem = (Item*)FindObject("Item");
        switch (pItem->GetItem())
        {
            //ボール出す
        case Item::ItemNum::BALL:
            Instantiate<FireFollowGround>(GetParent());
            hasItem_ = false;
            pItem->SetItem(Item::ItemNum::ITEM_MAX);
            break;
            //爆弾出す
        case Item::ItemNum::BOMB:
            Instantiate<Bomb>(GetParent());
            hasItem_ = false;
            pItem->SetItem(Item::ItemNum::ITEM_MAX);
            break;
        case Item::ItemNum::WING:
            //橋を渡っていなかったら
            if (!(IsOnBridge_) && hasItem_)
            {
                //ダッシュ
                IsSpeedUp_ = true;
                Instantiate<Line>(this);
                hasItem_ = false;
                pItem->SetItem(Item::ItemNum::ITEM_MAX);
            }
            break;
        default:
            break;
        }
    }


    //停止する
    if (Input::IsKeyDown(DIK_F))
    {
        if (!IsStop_)
        {
            speed_ = 0;
            IsStop_ = true;
        }
        else
        {
            speed_ = 0.3f;
            IsStop_ = false;
        }
    }

    /////////////////////////移動/////////////////////////
    //ジャンプ中の重力
    if (Input::IsKeyDown(DIK_SPACE) && transform_.position_.y <= 0.75f)
    {
        //初速度
        jump_v0 = 0.2;
        //重力
        gravity = 0.008f;

        //初速度を加える
        move_.y = jump_v0;

        //重力を加える
        move_.y += gravity;

        //ジャンプフラグ
        IsJump = true;
    }
}

void Player::InitBase()
{
    hModel_ = Model::Load("Model\\Player\\egg.fbx");
    assert(hModel_ >= 0);

    hModel2_ = Model::Load("Model\\Player\\duck.fbx");
    assert(hModel2_ >= 0);

    //位置
    transform_.rotate_ = XMFLOAT3(0, 180, 0);
    transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35);

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
    AddCollider(collision);

    Instantiate<Controller>(this);

    pText->Initialize();

    pParticle_ = Instantiate<Particle>(this);

    //最初は卵から
    CharacterState = State::EGG;
}

void Player::DrawBase()
{
    Model::SetTransform(hModel2_, transform_);
    Model::SetTransform(hModel_, transform_);

    switch (CharacterState)
    {
    case State::EGG:
        Model::FlashModel(hModel_);
        break;
    case State::GROWN:
        Model::FlashModel(hModel2_);
        break;
    }

    if (IsSpeedUp_)
    {
        float pos = -0.5f;
        for (int i = 0; i < 3; i++)
        {
            Transform trans = transform_;
            trans.position_.z += pos;
            pLine[i]->AddPosition(trans.position_);
            pLine[i]->SetWidth(0.1f);
            pLine[i]->SetColor(XMFLOAT4(1, 1, 1, 0.9));
            pLine[i]->Draw();
            pos += 0.5f;
        }
    }
}

void Player::ReleaseBase()
{
    //ポリライン解放
    for (int i = 0; i < 3; i++)
    {
        pLine[i]->Release();
    }
}

//何かに当たった
void Player::OnCollision(GameObject* pTarget)
{
    //敵に当たった
    if (pTarget->GetObjectName() == "Enemy" || pTarget->GetObjectName() == "Fire")
    {
        Model::SetIsFlash(hModel_);
        Model::SetIsFlash(hModel2_);

        if (starTime_ == 0)
        {
            if (starNum_ > 0)
            {
                starTime_++;
                starNum_--;
            }
        }
    }
    
    if (pTarget->GetObjectName() == "Star")
    {
        if (starTime_ == 0)
        {
            starTime_++;
            starNum_++;
        }
    }

    XMVECTOR vPlayerPos = XMLoadFloat3(&transform_.position_);
    XMVECTOR Down = { 0,-1,0,0 };

    //敵に当たった
    //if (pTarget->GetObjectName() == "EnemyMob")
    //{
    //    //敵の位置
    //    XMFLOAT3 EnemyPos = pTarget->GetPosition();
    //    XMVECTOR vEnemyPos = XMLoadFloat3(&EnemyPos);

    //    //プレイヤーの位置
    //    XMVECTOR PlayerPos = vEnemyPos - vPlayerPos;
    //    XMVector3Normalize(PlayerPos);

    //    //Downとプレイヤーの外積を求める
    //    XMVECTOR vDot = XMVector3Dot(Down, PlayerPos);
    //    float Dot = XMVectorGetY(vDot);

    //    //角度を求める
    //    angle = acos(Dot) * (180.0 / M_PI);

    //    if (angle <= 90)
    //    {
    //        //初速度
    //        jump_v0 = 0.15f;
    //        //重力
    //        gravity = 0.003f;

    //        //初速度を加える
    //        move_.y = jump_v0;
    //        transform_.position_.y += move_.y;

    //        //重力を加える
    //        move_.y += gravity;
    //        transform_.position_.y += move_.y;
    //    }
    //    else
    //    {
    //        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
    //        pSceneManager->ChangeScene(SCENE_ID_RESULT);
    //    }
    //}
}