#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Duck : public GameObject
{
    int hModel_;    //���f���ԍ�
public:
    //�R���X�g���N�^
    Duck(GameObject* parent);

    //�f�X�g���N�^
    ~Duck();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};