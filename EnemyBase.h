#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/PolyLine.h"
#include "Engine/Astar.h"
#include "Manager/EnemyEffect.h"
#include "Player.h"


//EnemyBaseを管理するクラス
class EnemyBase : public GameObject
{
protected:
    Player* pPlayer_;
    int hModel_;
    int count_;
    Astar AI_;
    bool CanMove_;
    int totalCell;
    int frame; //何フレーム毎に進むか

    virtual void Action() = 0;
    virtual void InitBase() = 0;
    virtual void ChangeColor() = 0;
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
};