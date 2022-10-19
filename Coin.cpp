#include "Coin.h"
#include "Player.h"

#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"

//コンストラクタ
Coin::Coin(GameObject* parent)
    :GameObject(parent, "Coin"), hModel_(-1)
{
}

//デストラクタ
Coin::~Coin()
{
}

//初期化
void Coin::Initialize()
{
    hModel_ = Model::Load("coin.fbx");
    assert(hModel_ >= 0);

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0.0f, 0.25f, 0.0f), 0.5f);
    AddCollider(collision);
}

void Coin::Update()
{
}

void Coin::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Coin::Release()
{
}

void Coin::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Player")
    {
        KillMe();
    }
}