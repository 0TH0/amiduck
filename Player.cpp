#include "Player.h"
#include "Stage.h"
#include "PlayScene.h"
#include "StartScene.h"
#include "Fire.h"
#include "FireFollowGround.h"
#include "Controller.h"
#include "Enemy.h"
#include "Line.h"
#include "Mushroom.h"
#include "Item.h"

#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"
#include "Engine/Math.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),

    //変数
    hModel_(-1), hModel2_(-1),
    jump_v0(0), gravity(0), angle(0), delay_(0),

    //フラグ
    IsJump(false), IsGround(false), hasItem_(false),IsLeft_(false),IsRight_(false),

    //定数
    speed_(0.3f), DUSHSPEED(0.05f),
    CAMERA_POS_Y(-15.0f), CAMERA_TAR_Y(-5.0f)
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
    hModel_ = Model::Load("Model\\Player\\egg.fbx");
    assert(hModel_ >= 0);

    hModel2_ = Model::Load("Model\\Player\\duck.fbx");
    assert(hModel2_ >= 0);

    //アニメーションの設定
    Model::SetAnimFrame(hModel_, 0, 200, 1.0f);

    //位置
    transform_.rotate_ = XMFLOAT3(0, 180, 0);
    transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35);

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
    AddCollider(collision);

    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);

    Instantiate<Controller>(this);

    pText->Initialize();

    pParticle_ = Instantiate<Particle>(this);

    //最初は卵から
    playerState = State::EGG;

    //ポリライン初期化
    for (int i = 0; i < 3; i++)
    {
        pLine[i] = new PoryLine;
        pLine[i]->Load("tex_orange.png");
    }
}

void Player::Update()
{
    switch (playerState)
    {
    case Player::State::EGG:
        transform_.rotate_.z += 10;
        break;
    case Player::State::LARVA:
        transform_.rotate_ = XMFLOAT3(0, 180, 0);
        break;
    }

    //星の数が０以下で卵
    if (starNum_ <= 0)
    {
        playerState = State::EGG;
    }
    else
    {
        playerState = State::LARVA;
    }

    // 1フレーム前の座標
    prevPosition = XMLoadFloat3(&transform_.position_);

    //あみだくじの処理
    LadderLottery();

    //アイテム使用
    if (Input::IsKeyDown(DIK_E))
    {
        Item* pItem =(Item*)FindObject("Item");
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
            Instantiate<Fire>(GetParent());
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
        }
    }

    //if (Input::IsKey(DIK_I))
    //{
    //    transform_.position_.x += 0.25;
    //}
    //if (Input::IsKey(DIK_K))
    //{
    //    transform_.position_.x -= 0.25;
    //}
    //if (Input::IsKey(DIK_L))
    //{
    //    transform_.position_.z -= 0.25;
    //}
    //if (Input::IsKey(DIK_J))
    //{
    //    transform_.position_.z += 0.25;
    //}

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

    pStage = (Stage*)FindObject("Stage");
    Enemy* pEnemy = (Enemy*)FindObject("Enemy");

    RotateDirMove();

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

    if (!IsStop_)
    {
        ////ジャンプ中の重力
        if (IsJump)
        {
            //重力
            move_.y -= gravity;
            transform_.position_.y += move_.y;
        }
        //ジャンプしてない時の重力
        else
        {
            //重力
            gravity = 0.1f;

            //重力を加える
            move_.y = -gravity;
            transform_.position_.y += move_.y;
        }
    }

    if (transform_.position_.y <= 0.75f)
    {
        transform_.position_.y = 0.75f;
    }

    if (starTime_ >= 10)
    {
        starTime_ = 0;
    }
    else if(starTime_ > 0)
    {
        starTime_++;
    }

    if (starNum_ >= 5)
    {
        starNum_ = 5;
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_CLEAR);
    }
}

void Player::Draw()
{
    Model::SetTransform(hModel2_, transform_);
    Model::SetTransform(hModel_, transform_);

    switch (playerState)
    {
    case State::EGG:
        Model::FlashModel(hModel_);
        break;
    case State::LARVA:
        Model::FlashModel(hModel2_);
        break;
    }

    //pText->Draw(100, 100, "Player:");
    //pText->Draw(250, 100, starNum_);

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

void Player::Release()
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
    if (pTarget->GetObjectName() == "Enemy" )
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
    if (pTarget->GetObjectName() == "Mushroom")
    {
        //敵の位置
        XMFLOAT3 EnemyPos = pTarget->GetPosition();
        XMVECTOR vEnemyPos = XMLoadFloat3(&EnemyPos);

        //プレイヤーの位置
        XMVECTOR PlayerPos = vEnemyPos - vPlayerPos;
        XMVector3Normalize(PlayerPos);

        //Downとプレイヤーの外積を求める
        XMVECTOR vDot = XMVector3Dot(Down, PlayerPos);
        float Dot = XMVectorGetY(vDot);

        //角度を求める
        angle = acos(Dot) * (180.0 / 3.14f);

        if (angle <= 90)
        {
            //初速度
            jump_v0 = 0.15f;
            //重力
            gravity = 0.003f;

            //初速度を加える
            move_.y = jump_v0;
            transform_.position_.y += move_.y;

            //重力を加える
            move_.y += gravity;
            transform_.position_.y += move_.y;
        }
        else
        {
            //横から当たったらゲームオーバー
            SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
            pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
        }
    }
}

//あみだくじ
void Player::LadderLottery()
{
    //////////////////壁との衝突判定///////////////////////
    XMINT3 obj = Math::ToXMINT(transform_.position_);
    
    //壁の判定(上)
    if (!IsRight_ && !IsLeft_)
    {
        //進行方向に道がなかったら戻ってくる
        if (pStage->IsEmpty(obj.x + 2, obj.z))
        {
            IsReturn_ = true;
        }
        if (pStage->IsEmpty(obj.x - 2, obj.z))
        {
            IsReturn_ = false;
        }
    }

    if (IsReturn_)
    {
        transform_.position_.x -= speed_;
    }
    else
    {
        transform_.position_.x += speed_;
    }


    ///////////////////////// あみだくじの処理 ///////////////////////////////////////////

    if (!IsLeft_ && StoppedTime_ > 4)
    {
        if (pStage->IsBridge(obj.x, obj.z - 4))
        {
            speed_ = 0;
            IsRight_ = true;
            StoppedTime_ = 0;
            IsOnBridge_ = true;
        }
    }

    //右に行く
    if (IsRight_)
    {
        IsStop_ = false;
        SpeedOnWood_[R] = 0.2;
        TimeOnWood_[R] += SpeedOnWood_[R];

        if (TimeOnWood_[R] >= 6)
        {
            TimeOnWood_[R] = 0;
            IsRight_ = false;
            IsOnBridge_ = false;
            delay_ = 0;
            SpeedOnWood_[R] = 0;


            switch (playerState)
            {
            case Player::State::EGG:
                speed_ = 0.2;
                break;
            case Player::State::LARVA:
                speed_ = 0.3f;
                break;
            default:
                break;
            }
        }
        else
        {
            //左に移動
            transform_.position_.z -= SpeedOnWood_[R];
        }
    }

    //左に行く
    else
    {
        //止まっていなかったら
        if (!IsStop_)
        {
            StoppedTime_++;

            if (!IsLeft_) delay_++;
        }

        //右に行ってからすぐに左に行かないように間隔を開ける
        if (delay_ > 4)
        {
            if (pStage->IsBridge(obj.x, obj.z + 3))
            {
                speed_ = 0;

                IsLeft_ = true;
                IsOnBridge_ = true;
            }
        }

        if (IsLeft_)
        {
            IsStop_ = false;
            SpeedOnWood_[L] = 0.2;
            TimeOnWood_[L] += SpeedOnWood_[L];

            if (TimeOnWood_[L] >= 6)
            {
                TimeOnWood_[L] = 0;
                IsLeft_ = false;
                IsOnBridge_ = false;
                delay_ = 0;
                StoppedTime_ = 0;
                SpeedOnWood_[L] = 0;

                switch (playerState)
                {
                case Player::State::EGG:
                    speed_ = 0.2;
                    break;
                case Player::State::LARVA:
                    speed_ = 0.3f;
                    break;
                default:
                    break;
                }
            }
            else
            {
                //右に移動
                transform_.position_.z += SpeedOnWood_[L];
            }
        }
    }
}

//進む方向を向く
void Player::RotateDirMove()
{
    //現在の位置ベクトル
    XMVECTOR nowPosition = XMLoadFloat3(&transform_.position_);

    //今回の移動ベクトル
    XMVECTOR move = nowPosition - prevPosition;

    //移動ベクトルの長さを測る
    XMVECTOR length = XMVector3Length(move);

    //0.1以上移動してたなら回転処理
    if (XMVectorGetX(length) > 0.1f)
    {
        //角度を求めるために長さを１にする（正規化）
        move = XMVector3Normalize(move);

        //基準となる奥向きのベクトル
        XMVECTOR front = { -1, 0, 0, 0 };

        //frontとmoveの内積を求める
        XMVECTOR vecDot = XMVector3Dot(front, move);
        float dot = XMVectorGetX(vecDot);

        //向いてる角度を求める（ラジアン）
        float angle = acos(dot);

        //frontとmoveの外積を求める
        XMVECTOR cross = XMVector3Cross(front, move);

        //外積の結果のYがマイナス　＝　下向き　＝　左に進んでる
        if (XMVectorGetY(cross) < 0)
        {
            angle *= -1;
        }

        //そのぶん回転させる
        transform_.rotate_.y = angle * 180.0f / 3.14f;
    }
}
