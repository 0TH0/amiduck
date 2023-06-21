#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Text.h"
#include "Engine/VFX.h"
#include "Engine/PolyLine.h"
#include "CharacterBase.h"

//◆◆◆を管理するクラス
class FireFollowGround : public CharacterBase
{
    PolyLine* pLine;
public:
    //コンストラクタ
    FireFollowGround(GameObject* parent);

    //デストラクタ
    ~FireFollowGround();

    void OnCollision(GameObject* pTarget) override;

    void Action() override;
    void Command() override;
    void InitBase() override;
    void DrawBase() override;
    void ReleaseBase() override;
};