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

    XMVECTOR SmoothStep(XMVECTOR V0, XMVECTOR V1, float t)
    {
        t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
        t = t * t * (3.f - 2.f * t);
        return XMVectorLerp(V0, V1, t);
    }
};