#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Text.h"
#include "Engine/Particle.h"
#include "Engine/PolyLine.h"
#include "CharacterBase.h"

//◆◆◆を管理するクラス
class Enemy : public CharacterBase
{
public:
    //コンストラクタ
    Enemy(GameObject* parent);

    //デストラクタ
    ~Enemy();

    void OnCollision(GameObject* pTarget) override;


    void Action() override;
    void Command() override;
    void InitBase() override;
    void DrawBase() override;
    void ReleaseBase() override;
};