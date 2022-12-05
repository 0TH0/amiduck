#include "Coin.h"
#include "PlayScene.h"
#include "Player.h"

#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

//コンストラクタ
Coin::Coin(GameObject* parent)
	: GameObject(parent, "Coin")
{
}

//初期化
void Coin::Initialize()
{
	hModel_ = Model::Load("Coin\\coin.fbx");
	assert(hPict_ >= 0);

	//当たり判定
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
	AddCollider(collision);
}

//更新
void Coin::Update()
{
	transform_.rotate_.y++;
}

//描画
void Coin::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Coin::Release()
{
}

void Coin::OnCollision(GameObject* pTarget)
{
	//敵に当たった
	if (pTarget->GetObjectName() == "Player")
	{
		Player* pPlayer = (Player*)FindObject("Player");
		pPlayer->PlusCoinCount(1);

		KillMe();
	}
}