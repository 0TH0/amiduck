#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Collider.h"
#include "Engine/PolyLine.h"

//���������Ǘ�����N���X
class CharacterBase : public GameObject
{
protected:

    //����
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
        GROWN,      //��������
    } CharacterState;

    int hModel_;              //���f���ԍ�
    int hModel2_;             //���f���ԍ�
    float jump_v0;            //�W�����v�̏����x
    float gravity;            //�d��
    float angle;              //�p�x
    XMFLOAT3 move_;           //�����x
    bool IsJump;              //�W�����v������
    bool IsGround;            //�n�ʂɂ��Ă��邩
    bool IsEnemy;             //�G�ɓ���������
    float speed_;             //�ړ����x
    float speedChange_;       //speed��ς���
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
    int starNum_;       //���̐�
    int starTime_;      //��������Ă���̎���
    bool hasItem_;      //�A�C�e���������Ă��邩

    //�萔
    Stage* pStage;
    Text* pText = new Text;
    Particle* pParticle_;
    EmitterData data;
    PolyLine* pLine[3];
    XMVECTOR prevPosition;

   virtual void Action() = 0;
   virtual void Command() = 0;
   virtual void InitBase() = 0;
   virtual void DrawBase() = 0;
   virtual void ReleaseBase() = 0;

public:
    //�R���X�g���N�^
    CharacterBase(GameObject* parent);
    //�p���p�R���X�g���N�^
    CharacterBase(GameObject* parent, std::string name);

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

    //���݂������̏���
    void LadderLottery();

    //�i�ޕ���������
    void  RotateDirMove();

    bool GetReturn() { return IsReturn_; };
    void SetHasItem(bool hasItem) { hasItem_ = hasItem; };
    bool GetHasItem() { return hasItem_; };
    int GetStarNum() { return  starNum_; };
    bool GetIsOnBridge() { return IsOnBridge_; };
};