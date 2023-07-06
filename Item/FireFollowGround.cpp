#include "FireFollowGround.h"
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
    static const int TIMEMAX = 200;
    static const float SPEED = 10.f;
    static const float DIS  = 7.f;
    static const float CENTER = 0.75f;
}

//�R���X�g���N�^
FireFollowGround::FireFollowGround(GameObject* parent)
    : GameObject(parent, "FireFollowGround"),hModel_(-1),pLine_()
{
}

//�f�X�g���N�^
FireFollowGround::~FireFollowGround()
{
}

//������
void FireFollowGround::Initialize()
{
    hModel_ = Model::Load("Model\\fire_blue.fbx");
    assert(hModel_ >= ZERO);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(ZERO, ZERO, ZERO), CENTER);
    AddCollider(collision);

    pLine_ = new PolyLine;
    pLine_->Load("Image\\line_white.png");
    assert(pLine_ != nullptr);

    Player* pPlayer = (Player*)FindObject("Player");
    transform_.position_ = pPlayer->GetPosition();

}

//�X�V
void FireFollowGround::Update()
{
    Player* pPlayer = (Player*)FindObject("Player");
    transform_.position_ = Transform::RotateAround(pPlayer->GetPosition(), DIS, SPEED);
    time_++;

    if (time_ >= TIMEMAX)
    {
        KillMe();
    }

    pLine_->AddPosition(transform_.position_);
}

//�`��
void FireFollowGround::Draw()
{
    pLine_->SetColor(BLUE);
    pLine_->Draw();
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void FireFollowGround::Release()
{
}

void FireFollowGround::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "EnemyBlue" ||
        pTarget->GetObjectName() == "EnemyGreen" ||
        pTarget->GetObjectName() == "EnemyRed" ||
        pTarget->GetObjectName() == "Fire")
    {
        pTarget->KillMe();
    }
}