#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Text.h"

//���������Ǘ�����N���X
class Player : public GameObject
{
    int hModel_;          //���f���ԍ�
    int hModelWood_;
    int hModelBlock_;
    float jump_v0;        //�W�����v�̏����x
    float GRAVITY;        //�d��
    float angle;          //�p�x
    XMFLOAT3 move_;       //�����x
    bool IsJump;          //�W�����v������
    bool IsCamera;        //�J�����𓮂�����
    bool IsGround;        //�n�ʂɂ��Ă��邩
    bool IsEnemy;         //�G�ɓ���������
    int BossHp;           //�{�X��HP

    //�萔
    float SPEED;        //�ړ����x
    const float DUSHSPEED;    //�_�b�V�����x
    const float CAMERA_TAR_Y; //�J�����̌���
    const float CAMERA_POS_Y; //�J�����̈ʒu
    float s;
    float t;
    float f;
    float g;

    Stage* pStage;

    Text* pText = new Text;

    float a = false;
    bool c = false;
    bool b = false;
    int time1 = 0;
    int time2;
    int time3;
    Transform trans[2];
    bool IsPress;
    bool IsReturn;

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

    float PlayerX() { return transform_.position_.x; }

    //void OnCollision(GameObject* pTarget) override;

    void FollowGround();

    bool GetReturn() { return IsReturn; };
};