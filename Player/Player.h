#pragma once
#include "../Engine/GameObject.h"
#include "../Stage/Stage.h"
#include "../Engine/Text.h"
#include "../Engine/VFX.h"
#include "../Engine/PolyLine.h"
#include "CharacterBase.h"
#include "../Item/Bomb.h"

static const int MAX_LINE = 3;

//Playerを管理するクラス
class Player : public CharacterBase
{
    Bomb* pBomb_;
    int hAudio_;
    PolyLine* pLine[MAX_LINE];
    int starNum_;
    int starAfterTime_;
    int starDelay_;
    float speedUp_;
    bool IsStar_;

public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    void Action() override;
    void Command() override;
    void InitBase() override;
    void DrawBase() override;
    void ReleaseBase() override;
    void OnCollision(GameObject* pTarget) override;

    int GetStarNum() { return starNum_; }
    int GetStarAfterTime() { return starAfterTime_; };
    void SetStarAfterTime(int time) { starAfterTime_ = time; };
    void ZeroStarAfterTime() { starAfterTime_ = ZERO; };
    void SetIsStar(bool IsStar) { IsStar_ = IsStar; };
    bool GetIsStar() { return IsStar_; };
};