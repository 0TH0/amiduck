#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Text.h"
#include "Engine/Particle.h"
#include "Engine/PoryLine.h"
#include "CharacterBase.h"

//���������Ǘ�����N���X
class Player : public CharacterBase
{
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