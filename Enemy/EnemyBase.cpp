#include "EnemyBase.h"
#include "../Engine/Collider.h"
#include "../Engine/Model.h"
#include "../Manager/AudioManager.h"
#include "../Manager/EffectManager.h"

namespace
{
    static const int ROTATE_Y = -90;      //Y回転
    static const float DIF_GOAL = 0.3f;     //目的地までの誤差調整
    static const float POS_Y = 0.7f;         //Y座標
    static const float LERP = 0.2f;         //補間する値
    static const float RADIUS = 0.5f;       //当たり判定サイズ
}

EnemyBase::EnemyBase(GameObject* parent, std::string name)
    : GameObject(parent, name), hModel_(-1),frameMove_(7),frameCount_(0),
      AI_(),CanMove_(false),totalCell_(0),v_(),pPlayer_(nullptr),prevPosition()
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize()
{
    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(ZERO, ZERO, ZERO), RADIUS);
    AddCollider(collision);

    transform_.position_.y = POS_Y;
    transform_.rotate_.y = ROTATE_Y;

    //初期化
    InitBase();
}

void EnemyBase::Update()
{
    prevPosition = XMLoadFloat3(&transform_.position_);
    pPlayer_ = (Player*)FindObject("Player");
    Stage* pStage = (Stage*)FindObject("Stage");

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

    RotateDirMove();
}

void EnemyBase::Draw()
{
    Model::SetOutLineDrawFlag(hModel_, true);
    //誤差修正
    Transform trans = transform_;
    trans.position_ = {transform_.position_.x - DIF_GOAL, POS_Y, transform_.position_.z - DIF_GOAL};

    Model::SetTransform(hModel_, trans);
    //各色変更
    ChangeColor();
    Model::Draw(hModel_);
}

void EnemyBase::Release()
{
    ReleaseBase();
}

void EnemyBase::OnCollision(GameObject* pTarget)
{
    //プレイヤーのアイテムに当たった
    if (pTarget->GetObjectName() == "Bomb" ||
        pTarget->GetObjectName() == "RotateAroundBall")
    {
        AudioManager::HitAudio();
        EffectManager::DieEffect(transform_.position_);
        KillMe();
    }
}

void EnemyBase::Move()
{
    //目的地に着いていない場合
    if (CanMove_ && totalCell_ >= 0)
    {
        //目的地までのベクトル
        v_ = { (float)AI_.GetToGoalCell(totalCell_).x + DIF_GOAL, POS_Y, (float)AI_.GetToGoalCell(totalCell_).z + DIF_GOAL, 0 };
        
        //線形補間
        transform_.position_ = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&transform_.position_), v_, LERP));
    }
}

void EnemyBase::RotateDirMove()
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
        XMVECTOR front = { 0, 0, 1, 0 };

        //frontとmoveの内積を求める
        XMVECTOR vecDot = XMVector3Dot(front, move);
        float dot = XMVectorGetX(vecDot);

        //向いてる角度を求める（ラジアン）
        float angle_ = acos(dot);

        //frontとmoveの外積を求める
        XMVECTOR cross = XMVector3Cross(front, move);

        //外積の結果のYがマイナス　＝　下向き　＝　左に進んでる
        if (XMVectorGetY(cross) < 0)
        {
            angle_ *= -1;
        }

        //そのぶん回転させる
        transform_.rotate_.y = angle_ * PI_DEGREES / M_PI;
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
