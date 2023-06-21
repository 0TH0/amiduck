#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Text.h"
#include "Engine/VFX.h"
#include "Engine/PolyLine.h"
#include "CharacterBase.h"
#include "Bomb.h"

//◆◆◆を管理するクラス
class Player : public CharacterBase
{
    Bomb* pBomb_;
    int hAudio_;
    PolyLine* pLine[3];
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
};