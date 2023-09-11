#include "Player.h"
#include "../Scene/PlayScene.h"
#include "../Item/RotateAroundBall.h"
#include "Controller.h"
#include "../Image/Line.h"
#include "../Item/Bomb.h"
#include "../Item/Item.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "../Engine/SphereCollider.h"
#include "../Engine/SceneManager.h"
#include "../Manager/AudioManager.h"
#include "../Engine/Color.h"

namespace
{
    static const float LINE_WIDTH = 0.1f;   //���̑���
    static const float DIF_LINE_POS = 0.5f; //���̈ʒu�덷
}

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :CharacterBase(parent, "Player"),hAudio_(-1), pBomb_(), speedUp_(0.5f),isStar_(false), starDelay_(0), 
    starNum_(0),starAfterTime_(0)
{
    for (int i = 0; i < MAX_LINE; i++)
    {
        pLine[i] = new PolyLine;
        pLine[i]->Load("Image\\tex_orange.png");
    }
}

//�f�X�g���N�^
Player::~Player()
{
}

void Player::Action()
{
    //�X�s�[�hUP��ԂȂ�
    if (IsSpeedUp_)
    {
        SpeedUpTime_++;
        speed_ = speedUp_;
    }
    //�X�s�[�hUP���Ă���P�b�o�߂�����
    if (SpeedUpTime_ > ONE_SECOND)
    {
        IsSpeedUp_ = false;
        SpeedUpTime_ = 0;
    }
    //�X�^�[������Ă���P�b�o�߂�����
    if (starDelay_ >= ONE_SECOND)
    {
        starDelay_ = 0;
    }
    else if (starDelay_ > 0)
    {
        starDelay_++;
    }
    //�X�^�[����肵����
    if (isStar_)
    {
        starAfterTime_++;
    }
    else
    {
        starAfterTime_ = 0;
    }
}

void Player::Command()
{
    //�A�C�e���g�p
    if (Input::IsKeyDown(DIK_E))
    {
        Item* pItem = (Item*)FindObject("Item");
        Instantiate<Bomb>(GetParent());
        //switch (pItem->GetItem())
        //{
        //    //�{�[���o��
        //case Item::ItemNum::BALL:
        //    Instantiate<RotateAroundBall>(GetParent());
        //    hasItem_ = false;
        //    pItem->SetItem(Item::ItemNum::ITEM_MAX);
        //    break;
        //    //���e�o��
        //case Item::ItemNum::BOMB:
        //    Instantiate<Bomb>(GetParent());
        //    hasItem_ = false;
        //    pItem->SetItem(Item::ItemNum::ITEM_MAX);
        //    break;
        //case Item::ItemNum::WING:
        //    //����n���Ă��Ȃ�������
        //    if (!(IsOnBridge_) && hasItem_)
        //    {
        //        //�_�b�V��
        //        IsSpeedUp_ = true;
        //        Instantiate<Line>(this);
        //        hasItem_ = false;
        //        pItem->SetItem(Item::ItemNum::ITEM_MAX);
        //    }
        //    break;
        //default:
        //    break;
        //}
    }

    //�W�����v
    if (Input::IsKeyDown(DIK_SPACE) && transform_.position_.y <= 0.75f)
    {
        //���ʉ�
        AudioManager::JumpAudio();

        //�d��
        gravity = 0.008f;

        //�����x��������
        move_.y = jumpV0_;

        //�d�͂�������
        move_.y += gravity;

        //�W�����v�t���O
        IsJump_ = true;
    }

    //��~����
    //if (Input::IsKeyDown(DIK_F))
    //{
    //    if (!IsStop_)
    //    {
    //        speed_ = 0;
    //        IsStop_ = true;
    //    }
    //    else
    //    {
    //        speed_ = 0.3f;
    //        IsStop_ = false;
    //    }
    //}
}

void Player::InitBase()
{
    hModel_ = Model::Load("Model/egg.fbx");
    assert(hModel_ >= 0);

    transform_.scale_ = XMFLOAT3(0.4f, 0.4f,0.4f);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
    AddCollider(collision);

    //�v���C���[�̃R���g���[���[
    Instantiate<Controller>(this);
}

void Player::DrawBase()
{
    Model::SetTransform(hModel_, transform_);
    Model::SetOutLineDrawFlag(hModel_, true);
    Model::Draw(hModel_);

    if (IsSpeedUp_)
    {
        float pos = DIF_LINE_POS;
        for (int i = 0; i < MAX_LINE; i++)
        {
            Transform trans = transform_;
            trans.position_.z += pos;
            pLine[i]->AddPosition(trans.position_);
            pLine[i]->SetWidth(LINE_WIDTH);
            pLine[i]->SetColor(WHITE);
            pLine[i]->Draw();
            pos -= DIF_LINE_POS;
        }
    }
}

void Player::ReleaseBase()
{
    //�|�����C�����
    for (int i = 0; i < MAX_LINE; i++)
    {
        pLine[i]->Release();
    }
}

//�����ɓ�������
void Player::OnCollision(GameObject* pTarget)
{
    //�ʂɓ���������
    if (pTarget->GetObjectName() == "EnemyWhite" || 
        pTarget->GetObjectName() == "EnemyYellow" ||
        pTarget->GetObjectName() == "EnemyGreen")
    {
        //�Q�[���I�[�o�[
        SetIsGameOver(true);
    }

    //���ɓ���������
    if (pTarget->GetObjectName() == "Star")
    {
        if (starDelay_ == 0)
        {
            starDelay_++;
            starNum_++;
            isStar_ = true;
        }
    }
}