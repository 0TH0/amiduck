#pragma once
#include "../Engine/GameObject.h"
#include "../Stage/Stage.h"
#include "../Engine/VFX.h"
#include "../Engine/PolyLine.h"

//���������Ǘ�����N���X
class RotateAroundBall : public GameObject
{
    PolyLine* pLine_;
    int hModel_;
public:
    //�R���X�g���N�^
    RotateAroundBall(GameObject* parent);

    //�f�X�g���N�^
    ~RotateAroundBall();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void OnCollision(GameObject* pTarget) override;
};