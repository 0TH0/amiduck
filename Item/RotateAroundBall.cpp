#include "RotateAroundBall.h"
#include "../Stage/Stage.h"
#include "../Scene/PlayScene.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "../Engine/SphereCollider.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Color.h"
#include "../Player.h"

namespace
{
    static const int   MAX_TIME = 200;
    static const float SPEED = 10.f;
    static const float DIS  = 7.f;
    static const float CENTER = 1.f;
}

//�R���X�g���N�^
RotateAroundBall::RotateAroundBall(GameObject* parent)
    : GameObject(parent, "RotateAroundBall"),hModel_(-1),pLine_()
{
}

//�f�X�g���N�^
RotateAroundBall::~RotateAroundBall()
{
}

//������
void RotateAroundBall::Initialize()
{
    hModel_ = Model::Load("Model\\fire.fbx");
    assert(hModel_ >= ZERO);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), CENTER);
    AddCollider(collision);

    pLine_ = new PolyLine;
    pLine_->Load("Image\\line_white.png");
    assert(pLine_ != nullptr);

    Player* pPlayer = (Player*)FindObject("Player");
    transform_.position_ = pPlayer->GetPosition();
    transform_.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5);

    Model::SetOutLineDrawFlag(hModel_, true);
}

//�X�V
void RotateAroundBall::Update()
{
    Player* pPlayer = (Player*)FindObject("Player");

    //�v���C���[�̎�������
    transform_.position_ = Transform::RotateAround(pPlayer->GetPosition(), DIS, SPEED);

    time_++;

    if (time_ >= MAX_TIME)
    {
        KillMe();
    }
    pLine_->AddPosition(transform_.position_);
}

//�`��
void RotateAroundBall::Draw()
{
    pLine_->SetColor(BLUE);
    pLine_->Draw();
    Model::SetColor(hModel_, BLUE);
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void RotateAroundBall::Release()
{
}

void RotateAroundBall::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "EnemyBlue" ||
        pTarget->GetObjectName() == "EnemyGreen" ||
        pTarget->GetObjectName() == "EnemyRed" ||
        pTarget->GetObjectName() == "Fire")
    {
        pTarget->KillMe();
    }
}