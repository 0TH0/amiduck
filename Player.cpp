#include "Player.h"
#include "Scene/PlayScene.h"
#include "FireFollowGround.h"
#include "Controller.h"
#include "Line.h"
#include "Bomb.h"
#include "Item.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"
#include "Engine/Audio.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :CharacterBase(parent, "Player"),hAudio_(-1), pBomb_()
{
    for (int i = 0; i < 3; i++)
    {
        pLine[i] = new PolyLine;
        pLine[i]->Load("Image\\tex_orange.png");
    }
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

    if (starDelay_ >= 60)
    {
        starDelay_ = 0;
    }
    else if (starDelay_ > 0)
    {
        starDelay_++;
    }

    if (IsStar_)
    {
        starAfterTime_++;
    }
    else
    {
        starAfterTime_ = 0;
    }
}

void Player::Command()
{
    //アイテム使用
    if (Input::IsKeyDown(DIK_E) && hasItem_)
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
    //if (Input::IsKeyDown(DIK_F))
    //{
    //    if (!IsStop_)
    //    {
    //        speed_ = 0;
    //        IsStop_ = true;
    //    }
    //    else
    //    {
    //        speed_ = 0.3f;
    //        IsStop_ = false;
    //    }
    //}

    /////////////////////////移動/////////////////////////
    //ジャンプ中の重力
    if (Input::IsKeyDown(DIK_SPACE) && transform_.position_.y <= 0.75f)
    {
        //効果音
        Audio::Play(hAudio_);

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
    hModel_[EGG] = Model::Load("Model\\Player\\egg.fbx");
    assert(hModel_[EGG] >= 0);

    hModel_[GROWN] = Model::Load("Model\\Player\\duck.fbx");
    assert(hModel_[GROWN] >= 0);

    hAudio_ = Audio::Load("Audio\\Jump.wav");
    assert(hAudio_ >= 0);

    //位置
    transform_.rotate_ = XMFLOAT3(0, 180, 0);
    transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35);

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
    AddCollider(collision);

    Instantiate<Controller>(this);

    //最初は卵から
    status_ = EGG;
}

void Player::DrawBase()
{
    Model::SetTransform(hModel_[EGG], transform_);
    Model::SetTransform(hModel_[GROWN], transform_);

    switch (status_)
    {
    case EGG:
        Model::Draw(hModel_[EGG]);
        break;
    case GROWN:
        Model::Draw(hModel_[GROWN]);
        break;
    default:
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
    //玉に当たったら
    if (pTarget->GetObjectName() == "EnemyRed" || 
        pTarget->GetObjectName() == "EnemyBlue" ||
        pTarget->GetObjectName() == "EnemyGreen")
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_RESULT);
    }

    if (pTarget->GetObjectName() == "Star")
    {
        if (starDelay_ == 0)
        {
            starDelay_++;
            starNum_++;
            IsStar_ = true;
        }
    }
}