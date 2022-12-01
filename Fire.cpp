#include "Fire.h"
#include "Engine/Model.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Player.h"

//コンストラクタ
Fire::Fire(GameObject* parent)
	: GameObject(parent, "Fire"), hModel_(-1)
{
}

//初期化
void Fire::Initialize()
{
	//画像データのロード
	hModel_ = Model::Load("fire.fbx");
	assert(hModel_ >= 0);
}

//更新
void Fire::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");

	plus = 1;
	time++;

	if (Input::IsKeyDown(DIK_SPACE))
	{
		if (!Is)
		{
			PlayerPosX_ = pPlayer->GetPosition().x;
			PlayerPosZ_ = pPlayer->GetPosition().z;
			Is = true;
		}
	}

	transform_.position_ = XMFLOAT3(PlayerPosX_, pPlayer->GetPosition().y + 3, PlayerPosZ_);

	if (time >= 90)
	{
		KillMe();
	}
	else
	{
		PlayerPosX_ += plus;
	}
}

//描画
void Fire::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Fire::Release()
{
}

