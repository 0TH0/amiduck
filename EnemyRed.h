#pragma once
#include "Engine/GameObject.h"
#include "Engine/Astar.h"
#include "Engine/VFX.h"

//���������Ǘ�����N���X
class EnemyRed : public GameObject
{
    XMFLOAT3 playerPos_;
    int count_;
    Astar AI_;
    bool CanMove_;
    int totalCell;
    int hModel_;
public:
    //�R���X�g���N�^
    EnemyRed(GameObject* parent);

    //�f�X�g���N�^
    ~EnemyRed();

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