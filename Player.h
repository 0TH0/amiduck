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
        L = 0,
        R,
        DIR_MAX
    };

    //プレイヤーの状態
    enum State
    {
        EGG = 0,    //卵
        LARVA, //幼虫
    } playerState;


    int hModel_;          //モデル番号
    int hModel2_;          //モデル番号

    float jump_v0;        //ジャンプの初速度
    float gravity;        //重力
    float angle;          //角度
    XMFLOAT3 move_;       //初速度
    bool IsJump;          //ジャンプしたか
    bool IsCamera;        //カメラを動かすか
    bool IsGround;        //地面についているか
    bool IsEnemy;         //敵に当たったか
    int BossHp;           //ボスのHP
    float speed_;        //移動速度
    float SpeedOnWood_[DIR_MAX];  //木の上の移動速度
    float TimeOnWood_[DIR_MAX];    //木の上の時間
    int SpeedUpTime_;             //スピードUPしている時間
    bool IsSpeedUp_;        //スピードUPしているか
    bool IsRight_;      //右に進んでいるか
    bool IsLeft_;       //左に進んでいるか
    int delay_;          //遅延
    int StoppedTime_;   //橋を渡ってからの時間
    bool IsReturn_;     //戻ってきているか
    bool IsStop_;       //止まっているか
    bool IsOnBridge_;   //橋の上にいるか
    int starCount_;

    //定数
    const float DUSHSPEED;    //ダッシュ速度
    const float CAMERA_TAR_Y; //カメラの向き
    const float CAMERA_POS_Y; //カメラの位置 

    Stage* pStage;
    Text* pText = new Text;
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

    void OnCollision(GameObject* pTarget) override;

    bool GetReturn() { return IsReturn_; };

    //あみだくじの処理
    void LadderLottery();
};