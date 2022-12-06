#pragma once
#include "Engine/GameObject.h"
#include "PoryLine.h"


//���������Ǘ�����N���X
class Player : public GameObject
{
    int hModel_;    //���f���ԍ�
    PoryLine* pLine;


public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};