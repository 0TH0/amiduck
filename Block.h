#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Block : public GameObject
{
    int hModel_;   //���f���ԍ�
public:
    //�R���X�g���N�^
    Block(GameObject* parent);

    //�f�X�g���N�^
    ~Block();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};

