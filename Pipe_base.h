#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Pipe_base : public GameObject
{
    int hModel_;   //���f���ԍ�
public:
    //�R���X�g���N�^
    Pipe_base(GameObject* parent);

    //�f�X�g���N�^
    ~Pipe_base();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};

