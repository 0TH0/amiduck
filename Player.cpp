#include "Player.h"
#include "Scene/PlayScene.h"
#include "Item/FireFollowGround.h"
#include "Controller.h"
#include "Image/Line.h"
#include "Item/Bomb.h"
#include "Item/Item.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"
#include "Engine/Audio.h"
#include "Engine/Color.h"

namespace
{
    static const float LINE_WIDTH = 0.1f;   //���̑���
    static const float DIF_LINE_POS = 0.5f; //���̈ʒu�덷
}

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :CharacterBase(parent, "Player"),hAudio_(-1), pBomb_(), speedUp_(0.4f),IsStar_(false), starDelay_(0), 
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
    if (IsStar_)
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
    if (Input::IsKeyDown(DIK_E) && hasItem_)
    {
        Item* pItem = (Item*)FindObject("Item");
        switch (pItem->GetItem())
        {
            //�{�[���o��
        case Item::ItemNum::BALL:
            Instantiate<FireFollowGround>(GetParent());
            hasItem_ = false;
            pItem->SetItem(Item::ItemNum::ITEM_MAX);
            break;
            //���e�o��
        case Item::ItemNum::BOMB:
            Instantiate<Bomb>(GetParent());
            hasItem_ = false;
            pItem->SetItem(Item::ItemNum::ITEM_MAX);
            break;
        case Item::ItemNum::WING:
            //����n���Ă��Ȃ�������
            if (!(IsOnBridge_) && hasItem_)
            {
                //�_�b�V��
                IsSpeedUp_ = true;
                Instantiate<Line>(this);
                hasItem_ = false;
                pItem->SetItem(Item::ItemNum::ITEM_MAX);
            }
            break;
        default:
            break;
        }
    }

    //�W�����v
    if (Input::IsKeyDown(DIK_SPACE) && transform_.position_.y <= 0.75f)
    {
        //���ʉ�
        Audio::Play(hAudio_);

        //�����x
        //jump_v0 = 0.2;
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
    hModel_[EGG] = Model::Load("Model\\Player\\egg.fbx");
    assert(hModel_[EGG] >= 0);

    hModel_[GROWN] = Model::Load("Model\\Player\\duck.fbx");
    assert(hModel_[GROWN] >= 0);

    hAudio_ = Audio::Load("Audio\\Jump.wav");
    assert(hAudio_ >= 0);

    //�ʒu
    transform_.rotate_ = XMFLOAT3(0, 180, 0);
    transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
    AddCollider(collision);

    Instantiate<Controller>(this);

    //�ŏ��͗�����
    status_ = EGG;
}

void Player::DrawBase()
{
    Model::SetTransform(hModel_[EGG], transform_);
    Model::SetTransform(hModel_[GROWN], transform_);

    switch (status_)
    {
    case EGG:
        Model::SetOutLineDrawFlag(hModel_[EGG], true);
        Model::Draw(hModel_[EGG]);
        break;
    case GROWN:
        Model::SetOutLineDrawFlag(hModel_[GROWN], true);
        Model::Draw(hModel_[GROWN]);
        break;
    default:
        break;
    }

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
    if (pTarget->GetObjectName() == "EnemyRed" || 
        pTarget->GetObjectName() == "EnemyBlue" ||
        pTarget->GetObjectName() == "EnemyGreen")
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_RESULT);
    }

    if (pTarget->GetObjectName() == "Star")
    {
        if (starDelay_ == 0)
        {
            starDelay_++;
            starNum_++;
            IsStar_ = true;
        }
    }
}