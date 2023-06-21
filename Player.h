#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Text.h"
#include "Engine/VFX.h"
#include "Engine/PolyLine.h"
#include "CharacterBase.h"
#include "Bomb.h"

//���������Ǘ�����N���X
class Player : public CharacterBase
{
    Bomb* pBomb_;
    int hAudio_;
    PolyLine* pLine[3];
public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    void Action() override;
    void Command() override;
    void InitBase() override;
    void DrawBase() override;
    void ReleaseBase() override;

    void OnCollision(GameObject* pTarget) override;
};