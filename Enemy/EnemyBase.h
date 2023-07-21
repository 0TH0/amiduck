#pragma once
#include "../Engine/GameObject.h"
#include "../Stage/Stage.h"
#include "../Engine/PolyLine.h"
#include "../Engine/Astar.h"
#include "../Engine/Color.h"
#include "../Manager/EnemyEffect.h"
#include "../Player/Player.h"

//EnemyBaseを管理するクラス
class EnemyBase : public GameObject
{
protected:
    int hModel_;        //モデル番号
    int frameCount_;    //フレーム計測
    Astar AI_;          //AI
    bool CanMove_;      //動いていいか
    int totalCell_;      //合計セル
    int frameMove_;     //何フレーム毎に進むか
    XMVECTOR v_;         //移動ベクトル
    Player* pPlayer_;   //プレイヤー

    //各行動
    virtual void Action() = 0;      
    //各初期化
    virtual void InitBase() = 0;
    //各色変更
    virtual void ChangeColor() = 0;
    //各解放
    virtual void ReleaseBase() = 0;

public:
    //継承用コンストラクタ
    EnemyBase(GameObject* parent, std::string name);

    //デストラクタ
    ~EnemyBase();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //目的に向かって動く
    void Move();

    //経路探索
    void Search(CELL goal);

    //セッターゲッター
    void SetFrameMove(int frameMove) { frameMove_ = frameMove; };
    int GetFrameMove() { return frameMove_; };
};