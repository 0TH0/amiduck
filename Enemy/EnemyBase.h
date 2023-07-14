#pragma once
#include "../Engine/GameObject.h"
#include "../Stage/Stage.h"
#include "../Engine/PolyLine.h"
#include "../Engine/Astar.h"
#include "../Engine/Color.h"
#include "../Manager/EnemyEffect.h"
#include "../Player.h"

//EnemyBase���Ǘ�����N���X
class EnemyBase : public GameObject
{
protected:
    int hModel_;        //���f���ԍ�
    int frameCount_;    //�t���[���v��
    Astar AI_;          //AI
    bool CanMove_;      //�����Ă�����
    int totalCell;      //���v�Z��
    int frame_;         //���t���[�����ɐi�ނ�
    XMVECTOR v;         //�ړ��x�N�g��
    Player* pPlayer_;   //�v���C���[

    //�e�s��
    virtual void Action() = 0;      
    //�e������
    virtual void InitBase() = 0;
    //�e�F�ύX
    virtual void ChangeColor() = 0;
    //�e���
    virtual void ReleaseBase() = 0;

public:
    //�p���p�R���X�g���N�^
    EnemyBase(GameObject* parent, std::string name);

    //�f�X�g���N�^
    ~EnemyBase();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�ړI�Ɍ������ē���
    void Move();

    //�o�H�T��
    void Search(CELL goal);
};