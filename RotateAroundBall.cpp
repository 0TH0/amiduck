#include "RotateAroundBall.h"
#include "Engine/Model.h"
#include "Engine/PolyLine.h"
#include "Player.h"

namespace
{
    PolyLine* pLine;
    Player* pPlayer;
}

//�R���X�g���N�^
RotateAroundBall::RotateAroundBall(GameObject* parent)
	: GameObject(parent, "RotateAroundBall")
{
}

//������
void RotateAroundBall::Initialize()
{
    hModel_ = Model::Load("Model\\fire_blue.fbx");
    assert(hModel_ >= 0);

    transform_.scale_ = XMFLOAT3(0.75, 0.75, 0.75);

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
    AddCollider(collision);

    pLine = new PolyLine;
    pLine->Load("Image\\line_white.png");
    assert(pLine != nullptr);

    pPlayer = (Player*)FindObject("Player");
    pPlayer->GetPosition();
}

//�X�V
void RotateAroundBall::Update()
{
    Transform::RotateAround(transform_.position_, 6, 2.f);
}

//�`��
void RotateAroundBall::Draw()
{
    pLine->SetColor(XMFLOAT4(1, 0.6, 1, 0.7));
    pLine->Draw();
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
        pTarget->GetObjectName() == "EnemyRed")
    {
        pTarget->KillMe();
    }
}