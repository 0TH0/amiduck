#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Text.h"

//◆◆◆を管理するクラス
class Player : public GameObject
{
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

    //定数
    float SPEED;        //移動速度
    const float DUSHSPEED;    //ダッシュ速度
    const float CAMERA_TAR_Y; //カメラの向き
    const float CAMERA_POS_Y; //カメラの位置
    float s;
    float t;
    float f;
    float g;

    Stage* pStage;

    Text* pText = new Text;

    float a = false;
    bool c = false;
    bool b = false;
    int time1 = 0;
    int time2;
    int time3;
    Transform trans[2];
    bool IsPress;
    bool IsReturn;

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

    //void OnCollision(GameObject* pTarget) override;

    void FollowGround();

    bool GetReturn() { return IsReturn; };
};