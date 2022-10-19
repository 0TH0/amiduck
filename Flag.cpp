#include "flag.h"
#include "Player.h"

#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"

//コンストラクタ
Flag::Flag(GameObject* parent)
    :GameObject(parent, "Coin"), hModel_(-1)
{
}

//デストラクタ
Flag::~Flag()
{
}

//初期化
void Flag::Initialize()
{
    hModel_ = Model::Load("Flag_Base.fbx");
    assert(hModel_ >= 0);

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0.0f, 0.25f, 0.0f), 0.1f);
    AddCollider(collision);
}

void Flag::Update()
{
}

void Flag::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Flag::Release()
{
}

void Flag::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Player")
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_CLEAR);
    }
}