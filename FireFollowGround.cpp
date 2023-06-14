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
#include "Engine/Text.h"

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
        pTarget->Invisible();

        Enemy* pEnemy = (Enemy*)FindObject("Enemy");

        if (starTime_ == 0 && pEnemy->GetStarNum() > 0)
        {
            starTime_++;
            Star* pStar = Instantiate<Star>(GetParent());
            pStar->SetPosition(pEnemy->GetPosition().x, pEnemy->GetPosition().y + 4, pEnemy->GetPosition().z);
        }
        KillMe();
    }
}

void FireFollowGround::Action()
{
}

void FireFollowGround::Command()
{
}

void FireFollowGround::InitBase()
{
}

void FireFollowGround::DrawBase()
{
}

void FireFollowGround::ReleaseBase()
{
}
