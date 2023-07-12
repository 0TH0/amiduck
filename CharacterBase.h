#pragma once
#include "Engine/GameObject.h"
#include "Stage/Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Collider.h"
#include "Engine/PolyLine.h"

//◆◆◆を管理するクラス
class CharacterBase : public GameObject
{
protected:

    //方向
    enum dir
    {
        L = 0,
        R,
        DIR_MAX
    };

    //プレイヤーの状態
    enum Status
    {
        EGG = 0,    //卵
        GROWN,      //成長した
        STATUS_MAX
    } status_;

    int hModel_[STATUS_MAX];              //モデル番号
    float jumpV0_;            //ジャンプの初速度
    float gravity;            //重力
    float angle_;              //角度
    XMFLOAT3 move_;           //初速度
    bool IsJump_;              //ジャンプしたか
    bool IsGround_;            //地面についているか
    bool IsEnemy;             //敵に当たったか
    float speed_;             //移動速度
    float speedChange_;       //speedを変える
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
    bool hasItem_;      //アイテムを持っているか

    //定数
    Stage* pStage;
    
    EmitterData data;
    XMVECTOR prevPosition;
    virtual void Action() = 0;
    virtual void Command() = 0;
    virtual void InitBase() = 0;
    virtual void DrawBase() = 0;
    virtual void ReleaseBase() = 0;

public:
    //継承用コンストラクタ
    CharacterBase(GameObject* parent, std::string name);

    //デストラクタ
    ~CharacterBase();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //あみだくじの処理
    void LadderLottery();

    //進む方向を向く
    void  RotateDirMove();

    bool GetReturn() { return IsReturn_; };
    void SetHasItem(bool hasItem) { hasItem_ = hasItem; };
    bool GetHasItem() { return hasItem_; };
    bool GetIsOnBridge() { return IsOnBridge_; };
};