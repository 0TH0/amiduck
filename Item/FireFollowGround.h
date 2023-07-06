#pragma once
#include "../Engine/GameObject.h"
#include "../Stage.h"
#include "../Engine/VFX.h"
#include "../Engine/PolyLine.h"

//���������Ǘ�����N���X
class FireFollowGround : public GameObject
{
    PolyLine* pLine_;
    int hModel_;
public:
    //�R���X�g���N�^
    FireFollowGround(GameObject* parent);

    //�f�X�g���N�^
    ~FireFollowGround();

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