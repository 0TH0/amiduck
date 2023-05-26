#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Text.h"
#include "Engine/Particle.h"
#include "Engine/PoryLine.h"

//���������Ǘ�����N���X
class CharacterBase : public GameObject
{
    enum dir
    {
        L = 0,
        R,
        DIR_MAX
    };

    //�v���C���[�̏��
    enum class State
    {
        EGG = 0,    //��
        LARVA, //�c��
    } CharacterBaseState;

    int hModel_;          //���f���ԍ�
    int hModel2_;          //���f���ԍ�

    float jump_v0;        //�W�����v�̏����x
    float gravity;        //�d��
    float angle;          //�p�x
    XMFLOAT3 move_;       //�����x
    bool IsJump;          //�W�����v������
    bool IsGround;        //�n�ʂɂ��Ă��邩
    bool IsEnemy;         //�G�ɓ���������
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
    int starNum_;
    int starTime_;
    bool hasItem_;

    //�萔
    const float DUSHSPEED;    //�_�b�V�����x
    const float CAMERA_TAR_Y; //�J�����̌���
    const float CAMERA_POS_Y; //�J�����̈ʒu 

    Stage* pStage;
    Particle* pParticle_;
    EmitterData data;
    PoryLine* pLine[3];
    XMVECTOR prevPosition;

public:
    //�R���X�g���N�^
    CharacterBase(GameObject* parent);

    //�f�X�g���N�^
    ~CharacterBase();

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

    void SetHasItem(bool hasItem) { hasItem_ = hasItem; };
    bool GetHasItem() { return hasItem_; };

    //�i�ޕ���������
    void  RotateDirMove();

    int GetStarNum() { return  starNum_; };

    bool GetIsOnBridge() { return IsOnBridge_; };
};