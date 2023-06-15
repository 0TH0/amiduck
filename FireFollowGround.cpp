#include "FireFollowGround.h"
#include "Stage.h"
#include "Scene/PlayScene.h"
#include "Scene/StartScene.h"
#include "Star.h"
#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Player.h"

FireFollowGround::FireFollowGround(GameObject* parent)
    :CharacterBase(parent, "FireFollowGround")
{
}

FireFollowGround::~FireFollowGround()
{
}

void FireFollowGround::OnCollision(GameObject* pTarget)
{
    //“G‚É“–‚½‚Á‚½
    if (pTarget->GetObjectName() == "Enemy")
    {
        Enemy* pEnemy = (Enemy*)FindObject("Enemy");

        if (starTime_ == 0 && pEnemy->GetStarNum() > 0)
        {
            //“G‚É“–‚½‚Á‚½‚ç¯‚ğ—‚Æ‚·
            starTime_++;
            Star* pStar = Instantiate<Star>(GetParent());
            pStar->SetPosition(pEnemy->GetPosition().x, pEnemy->GetPosition().y + 4, pEnemy->GetPosition().z);
        }
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
    transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35);

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
