#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Text.h"
#include "Engine/VFX.h"
#include "Engine/PolyLine.h"
#include "CharacterBase.h"

//���������Ǘ�����N���X
class FireFollowGround : public CharacterBase
{
    PolyLine* pLine;
public:
    //�R���X�g���N�^
    FireFollowGround(GameObject* parent);

    //�f�X�g���N�^
    ~FireFollowGround();

    void OnCollision(GameObject* pTarget) override;

    void Action() override;
    void Command() override;
    void InitBase() override;
    void DrawBase() override;
    void ReleaseBase() override;
};