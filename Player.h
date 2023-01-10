#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Text.h"
#include "Engine/Particle.h"

//���������Ǘ�����N���X
class Player : public GameObject
{
    enum dir
    {
        L = 0,
        R,
        DIR_MAX
    };

    //�v���C���[�̏��
    enum State
    {
        EGG = 0,    //��
        LARVA, //�c��
    } playerState;


    int hModel_;          //���f���ԍ�
    int hModel2_;          //���f���ԍ�

    float jump_v0;        //�W�����v�̏����x
    float gravity;        //�d��
    float angle;          //�p�x
    XMFLOAT3 move_;       //�����x
    bool IsJump;          //�W�����v������
    bool IsCamera;        //�J�����𓮂�����
    bool IsGround;        //�n�ʂɂ��Ă��邩
    bool IsEnemy;         //�G�ɓ���������
    int BossHp;           //�{�X��HP
    float speed_;        //�ړ����x
    float SpeedOnWood_[DIR_MAX];  //�؂̏�̈ړ����x
    float TimeOnWood_[DIR_MAX];    //�؂̏�̎���
    int SpeedUpTime_;             //�X�s�[�hUP���Ă��鎞��
    bool IsSpeedUp_;        //�X�s�[�hUP���Ă��邩
    bool IsRight_;      //�E�ɐi��ł��邩
    bool IsLeft_;       //���ɐi��ł��邩
    int delay_;          //�x��
    int StoppedTime_;   //����n���Ă���̎���
    bool IsReturn_;     //�߂��Ă��Ă��邩
    bool IsStop_;       //�~�܂��Ă��邩
    bool IsOnBridge_;   //���̏�ɂ��邩
    int starCount_;

    //�萔
    const float DUSHSPEED;    //�_�b�V�����x
    const float CAMERA_TAR_Y; //�J�����̌���
    const float CAMERA_POS_Y; //�J�����̈ʒu 

    Stage* pStage;
    Text* pText = new Text;
    Particle* pParticle_;
    EmitterData data;

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

    void OnCollision(GameObject* pTarget) override;

    bool GetReturn() { return IsReturn_; };

    //���݂������̏���
    void LadderLottery();
};