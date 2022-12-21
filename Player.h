#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Text.h"
#include "Engine/Particle.h"

//◆◆◆を管理するクラス
class Player : public GameObject
{
    enum dir
    {
        left = 0,
        right,
        dir_max
    };

    int hModel_;          //モデル番号
    int hModelWood_;
    int hModelBlock_;
    float jump_v0;        //ジャンプの初速度
    float GRAVITY;        //重力
    float angle;          //角度
    XMFLOAT3 move_;       //初速度
    bool IsJump;          //ジャンプしたか
    bool IsCamera;        //カメラを動かすか
    bool IsGround;        //地面についているか
    bool IsEnemy;         //敵に当たったか
    int BossHp;           //ボスのHP

    float speed_;        //移動速度
    float speed_on_wood_[dir_max];  //木の上の移動速度
    float time_on_wood_[dir_max];    //木の上の時間
    int speed_up_time_;             //スピードUPしている時間
    bool is_Speed_up_;

    //定数
    const float DUSHSPEED;    //ダッシュ速度
    const float CAMERA_TAR_Y; //カメラの向き
    const float CAMERA_POS_Y; //カメラの位置

    Stage* pStage;

    Text* pText = new Text;

    bool IsRight_ = false;
    bool c = false;
    bool IsLeft_ = false;
    int delay;          //遅延
    int stopped_time_;
    int time3;
    Transform trans[2];
    bool IsPress;
    bool IsReturn;
    bool IsStop;
    bool is_on_bridge_;

    int coin_count_;
    XMFLOAT3 EnemyPos_;
    XMMATRIX mat_;

    Particle* pParticle_;
    EmitterData data;

public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    float PlayerX() { return transform_.position_.x; }

    void OnCollision(GameObject* pTarget) override;

    void FollowGround();

    bool GetReturn() { return IsReturn; };

    void Amidakuji();


    //Coin
    int GetCoinCount() { return coin_count_; };

    void PlusCoinCount(int count) { coin_count_ += count; };

    void MinCoinCount(int count) { coin_count_ -= count; };
};