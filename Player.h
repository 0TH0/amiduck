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
        left = 0,
        right,
        dir_max
    };

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

    float speed_;        //�ړ����x
    float speed_on_wood_[dir_max];  //�؂̏�̈ړ����x
    float time_on_wood_[dir_max];    //�؂̏�̎���
    int speed_up_time_;             //�X�s�[�hUP���Ă��鎞��
    bool is_Speed_up_;

    //�萔
    const float DUSHSPEED;    //�_�b�V�����x
    const float CAMERA_TAR_Y; //�J�����̌���
    const float CAMERA_POS_Y; //�J�����̈ʒu

    Stage* pStage;

    Text* pText = new Text;

    bool IsRight_ = false;
    bool c = false;
    bool IsLeft_ = false;
    int delay;          //�x��
    int stopped_time_;
    int time3;
    Transform trans[2];
    bool IsPress;
    bool IsReturn;
    bool IsStop;
    bool is_on_bridge_;

    int coin_count_;
    XMFLOAT3 EnemyPos_;
    XMMATRIX mat_;

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

    float PlayerX() { return transform_.position_.x; }

    void OnCollision(GameObject* pTarget) override;

    void FollowGround();

    bool GetReturn() { return IsReturn; };

    void Amidakuji();


    //Coin
    int GetCoinCount() { return coin_count_; };

    void PlusCoinCount(int count) { coin_count_ += count; };

    void MinCoinCount(int count) { coin_count_ -= count; };
};