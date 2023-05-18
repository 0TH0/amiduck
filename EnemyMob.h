#pragma once
#include "CharacterBase.h"
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Astar.h"

//���������Ǘ�����N���X
class EnemyMob : public GameObject
{
    int EnemyTime_;
    XMFLOAT3 playerPos_;
    int count_;
    Astar AI_;
    bool CanMove_;
    int totalCell;
    int hModel_;
public:
    //�R���X�g���N�^
    EnemyMob(GameObject* parent);

    //�f�X�g���N�^
    ~EnemyMob();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void Action();
};