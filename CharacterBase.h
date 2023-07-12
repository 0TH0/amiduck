#pragma once
#include "Engine/GameObject.h"
#include "Stage/Stage.h"
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
    enum Status
    {
        EGG = 0,    //��
        GROWN,      //��������
        STATUS_MAX
    } status_;

    int hModel_[STATUS_MAX];              //���f���ԍ�
    float jumpV0_;            //�W�����v�̏����x
    float gravity;            //�d��
    float angle_;              //�p�x
    XMFLOAT3 move_;           //�����x
    bool IsJump_;              //�W�����v������
    bool IsGround_;            //�n�ʂɂ��Ă��邩
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
    bool hasItem_;      //�A�C�e���������Ă��邩

    //�萔
    Stage* pStage;
    
    EmitterData data;
    XMVECTOR prevPosition;
    virtual void Action() = 0;
    virtual void Command() = 0;
    virtual void InitBase() = 0;
    virtual void DrawBase() = 0;
    virtual void ReleaseBase() = 0;

public:
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
    bool GetIsOnBridge() { return IsOnBridge_; };
};