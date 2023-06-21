#pragma once
#include "Engine/GameObject.h"
#include "Engine/Astar.h"
#include "Engine/Particle.h"

//���������Ǘ�����N���X
class EnemyGreen : public GameObject
{
    XMFLOAT3 playerPos_;
    int count_;
    Astar AI_;
    bool CanMove_;
    int totalCell;
    int hModel_;
    int randX_;
    int randZ_;
public:
    //�R���X�g���N�^
    EnemyGreen(GameObject* parent);

    //�f�X�g���N�^
    ~EnemyGreen();

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