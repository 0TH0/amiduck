#include "Player.h"
#include "Scene/PlayScene.h"
#include "FireFollowGround.h"
#include "Controller.h"
#include "Enemy.h"
#include "Line.h"
#include "Bomb.h"
#include "Item.h"
#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"
#include "Engine/Audio.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :CharacterBase(parent, "Player")
{
}

//�f�X�g���N�^
Player::~Player()
{
}

void Player::Action()
{
    if (IsSpeedUp_)
    {
        SpeedUpTime_++;
        speed_ = 0.4;
    }
    if (SpeedUpTime_ > 60)
    {
        IsSpeedUp_ = false;
        SpeedUpTime_ = 0;
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

    /////////////////////////�ړ�/////////////////////////
    //�W�����v���̏d��
    if (Input::IsKeyDown(DIK_SPACE) && transform_.position_.y <= 0.75f)
    {
        //���ʉ�
        Audio::Play(hAudio_);

        //�����x
        jump_v0 = 0.2;
        //�d��
        gravity = 0.008f;

        //�����x��������
        move_.y = jump_v0;

        //�d�͂�������
        move_.y += gravity;

        //�W�����v�t���O
        IsJump = true;
    }
}

void Player::InitBase()
{
    hModel_ = Model::Load("Model\\Player\\egg.fbx");
    assert(hModel_ >= 0);

    hModel2_ = Model::Load("Model\\Player\\duck.fbx");
    assert(hModel2_ >= 0);

    hAudio_ = Audio::Load("Audio\\Jump.wav");
    assert(hAudio_ >= 0);

    //�ʒu
    transform_.rotate_ = XMFLOAT3(0, 180, 0);
    transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
    AddCollider(collision);

    Instantiate<Controller>(this);

    pParticle_ = Instantiate<Particle>(this);

    //�ŏ��͗�����
    CharacterState = State::EGG;
}

void Player::DrawBase()
{
    Model::SetTransform(hModel2_, transform_);
    Model::SetTransform(hModel_, transform_);

    switch (CharacterState)
    {
    case State::EGG:
        Model::FlashModel(hModel_);
        break;
    case State::GROWN:
        Model::FlashModel(hModel2_);
        break;
    }

    if (IsSpeedUp_)
    {
        float pos = -0.5f;
        for (int i = 0; i < 3; i++)
        {
            Transform trans = transform_;
            trans.position_.z += pos;
            pLine[i]->AddPosition(trans.position_);
            pLine[i]->SetWidth(0.1f);
            pLine[i]->SetColor(XMFLOAT4(1, 1, 1, 0.9));
            pLine[i]->Draw();
            pos += 0.5f;
        }
    }
}

void Player::ReleaseBase()
{
    //�|�����C�����
    for (int i = 0; i < 3; i++)
    {
        pLine[i]->Release();
    }
}

//�����ɓ�������
void Player::OnCollision(GameObject* pTarget)
{
    //�G�ɓ�������
    if (pTarget->GetObjectName() == "Enemy" || pTarget->GetObjectName() == "Fire")
    {
        Model::SetIsFlash(hModel_);
        Model::SetIsFlash(hModel2_);

        if (starTime_ == 0)
        {
            if (starNum_ > 0)
            {
                starTime_++;
                starNum_--;
            }
        }
    }
    
    if (pTarget->GetObjectName() == "Star")
    {
        if (starTime_ == 0)
        {
            starTime_++;
            starNum_++;
        }
    }

    //�ʂɓ���������
    if (pTarget->GetObjectName() == "EnemyRed" || 
        pTarget->GetObjectName() == "EnemyBlue" ||
        pTarget->GetObjectName() == "EnemyGreen")
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_RESULT);
    }
}