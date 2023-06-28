#include "FireFollowGround.h"
#include "Stage.h"
#include "Scene/PlayScene.h"
#include "Star.h"

#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Player.h"

FireFollowGround::FireFollowGround(GameObject* parent)
    :CharacterBase(parent, "FireFollowGround"), pLine()
{
}

FireFollowGround::~FireFollowGround()
{
}

void FireFollowGround::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "EnemyBlue" ||
        pTarget->GetObjectName() == "EnemyGreen" ||
        pTarget->GetObjectName() == "EnemyRed")
    {
        pTarget->KillMe();
    }
}

void FireFollowGround::Action()
{
    time_++;

    if (time_ >= 360)
    {
        KillMe();
    }

    pLine->AddPosition(transform_.position_);
}

void FireFollowGround::Command()
{
}

void FireFollowGround::InitBase()
{
    hModel_ = Model::Load("Model\\fire_blue.fbx");
    assert(hModel_ >= 0);

    //ˆÊ’u
    transform_.scale_ = XMFLOAT3(0.75, 0.75, 0.75);

    //“–‚½‚è”»’è
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
    AddCollider(collision);

    pLine = new PolyLine;
    pLine->Load("Image\\line_white.png");
    assert(pLine != nullptr);

    Player* pPlayer = (Player*)FindObject("Player");
    transform_.position_ = pPlayer->GetPosition();

    speed_ = 0.6f;
    speedChange_ = 0.6f;

    IsReturn_ = pPlayer->GetReturn();
}

void FireFollowGround::DrawBase()
{
    pLine->SetColor(XMFLOAT4(1, 0.6, 1, 0.7));
    pLine->Draw();
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void FireFollowGround::ReleaseBase()
{
}
