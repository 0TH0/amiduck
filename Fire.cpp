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
	
	PlayerPosX_ = pPlayer->GetPosition().x;

	PlayerPosZ_ = pPlayer->GetPosition().z;

	if (Input::IsKeyDown(DIK_SPACE))
	{
		transform_.position_ = XMFLOAT3(PlayerPosX_, 0 ,PlayerPosZ_);
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

