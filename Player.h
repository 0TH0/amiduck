#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Text.h"
#include "Engine/Particle.h"
#include "Engine/PoryLine.h"
#include "CharacterBase.h"

//◆◆◆を管理するクラス
class Player : public CharacterBase
{
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