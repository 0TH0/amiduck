#include "CharacterBase.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"

CharacterBase::CharacterBase(GameObject* parent, std::string name)
	: GameObject(parent, name),pStage(nullptr), data(), prevPosition(), 
      status_(EGG), jump_v0(),gravity(0),angle(0),move_(),speed_(0.3f),SpeedUpTime_(0),
      IsJump(false), IsGround(false), IsEnemy(false), IsReturn_(false), IsSpeedUp_(false),IsRight_(false),IsLeft_(false),
      IsStop_(false), IsOnBridge_(false),
      delay_(0),StoppedTime_(0),hasItem_(0),speedChange_(0.2f)
{
    for (int i = 0; i < Status::STATUS_MAX; i++)
    {
        hModel_[i] = -1;
    }

    for (int i = 0; i < DIR_MAX; i++)
    {
        SpeedOnWood_[i] = 0;
        TimeOnWood_[i] = 0;
    }
}

//デストラクタ
CharacterBase::~CharacterBase()
{
}

//初期化
void CharacterBase::Initialize()
{
	InitBase();
}

//更新
void CharacterBase::Update()
{
    pStage = (Stage*)FindObject("Stage");

    switch (status_)
    {
    case EGG:
        transform_.rotate_.z += 10;
        break;
    case GROWN:
        transform_.rotate_ = XMFLOAT3(0, 180, 0);
        break;
    default:
        break;
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

    Command();
    Action();

    // 1フレーム前の座標
    prevPosition = XMLoadFloat3(&transform_.position_);

    //あみだくじの処理
    LadderLottery();

    //進行方向に回転する
    RotateDirMove();
}

//描画
void CharacterBase::Draw()
{
	DrawBase();
}

//開放
void CharacterBase::Release()
{
}

void CharacterBase::LadderLottery()
{
    //////////////////壁との衝突判定///////////////////////
    XMINT3 obj = ToXMINT({ transform_.position_ .x + 0.4f, transform_.position_.y ,transform_.position_.z });

    //壁の判定(上)
    if (!IsRight_ && !IsLeft_)
    {
        //進行方向に道がなかったら戻ってくる
        if (pStage->IsCorner(obj.x + 1, obj.z))
        {
            IsReturn_ = true;
        }
        if (pStage->IsCorner(obj.x - 1, obj.z))
        {
            IsReturn_ = false;
        }
    }

    if (transform_.position_.x <= 0)
    {
        IsReturn_ = false;
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
    if (!IsLeft_ && StoppedTime_ > 5)
    {
        if (pStage->IsBridge(obj.x, obj.z - 1))
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

            switch (status_)
            {
            case EGG:
                speed_ = speedChange_;
                break;
            case GROWN:
                speed_ = speedChange_ * 2;
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
        if (delay_ > 5)
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

                switch (status_)
                {
                case EGG:
                    speed_ = speedChange_;
                    break;
                case GROWN:
                    speed_ = speedChange_ * 2;
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

void CharacterBase::RotateDirMove()
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