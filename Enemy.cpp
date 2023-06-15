#include "Scene/PlayScene.h"
#include "Scene/StartScene.h"
#include "Controller.h"
#include "Enemy.h"
#include "Line.h"
#include "Star.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"
#include "Player.h"

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
    :CharacterBase(parent, "Enemy")
{
}

//�f�X�g���N�^
Enemy::~Enemy()
{
}

//�����ɓ�������
void Enemy::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Fire" || pTarget->GetObjectName() == "FireFollowGround")
    {
        if (starTime_ == 0 && starNum_ > 0)
        {
            starTime_++;
            Model::SetIsFlash(hModel_);
            Model::SetIsFlash(hModel2_);
            starNum_--;
        }
    }

    //�G�ɓ�������
    if (pTarget->GetObjectName() == "Player")
    {
        Player* pPlayer = (Player*)FindObject("Player");
        if (starTime_ == 0 && pPlayer->GetStarNum() > 0)
        {
            starTime_++;
            Star* pStar = Instantiate<Star>(GetParent());
            
            pStar->SetPosition(pPlayer->GetPosition().x, pPlayer->GetPosition().y + 4, pPlayer->GetPosition().z);
        }
    }

    if (pTarget->GetObjectName() == "Star")
    {
        if (starTime_ == 0)
        {
            starTime_++;
            CharacterState = State::GROWN;
            starNum_++;
        }
    }
}

void Enemy::Action()
{
}

void Enemy::Command()
{
}

void Enemy::InitBase()
{
    hModel_ = Model::Load("Model\\Player\\egg.fbx");
    assert(hModel_ >= 0);

    hModel2_ = Model::Load("Model\\Enemy\\raccoon.fbx");
    assert(hModel2_ >= 0);

    //�A�j���[�V�����̐ݒ�
    Model::SetAnimFrame(hModel_, 0, 200, 1.0f);

    //�ʒu
    transform_.rotate_ = XMFLOAT3(0, 180, 0);
    transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
    AddCollider(collision);

    //Instantiate<Controller>(this);

    pText->Initialize();

    pParticle_ = Instantiate<Particle>(this);

    //�ŏ��͗�����
    CharacterState = State::EGG;

    Model::SetColor(hModel_, XMFLOAT4(1, 1, 1, 1));
}

void Enemy::DrawBase()
{
    Model::SetTransform(hModel2_, transform_);
    Model::SetTransform(hModel_, transform_);

    //���f���̐F
    switch (CharacterState)
    {
    case State::EGG:
        Model::FlashModel(hModel_);
        break;
    case State::GROWN:
        Model::FlashModel(hModel2_);
        break;
    }
}

void Enemy::ReleaseBase()
{
}
