#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Pipe : public GameObject
{
    int hModel_;   //���f���ԍ�
public:
    //�R���X�g���N�^
    Pipe(GameObject* parent);

    //�f�X�g���N�^
    ~Pipe();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};

