#include "Bomb.h"
#include "../Engine/Model.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"
#include "../Player/Player.h"
#include "../Manager/EffectManager.h"
#include "../Manager/AudioManager.h"

namespace
{
	static const int MAX_TIME = 100;
	static const int MAX_STAR_DELAY = 7;
}

//コンストラクタ
Bomb::Bomb(GameObject* parent)
	: GameObject(parent, "Bomb"), hModel_(-1)
{
}

Bomb::~Bomb()
{
}

//初期化
void Bomb::Initialize()
{
	//画像データのロード
	hModel_ = Model::Load("Model\\bomb.fbx");
	assert(hModel_ >= 0);

	//当たり判定
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1.5f);
	AddCollider(collision);

	transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35);

	transform_.rotate_ = XMFLOAT3(0, 0, 0);

	//初期位置はプレイヤーの位置のｙ＋１
	Player* pPlayer = (Player*)FindObject("Player");
	IsReturn_ = pPlayer->GetReturn();
	PlayerTrans_.position_ = pPlayer->GetPosition();
	transform_.position_ = PlayerTrans_.position_;
	transform_.position_.y = PlayerTrans_.position_.y + 1;
}

//更新
void Bomb::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");
	transform_.rotate_.x += 5;

	EffectManager::BombEffect(transform_.position_);
	time++;

	data.position = transform_.position_;
	
	if (time >= MAX_TIME)
	{
		KillMe();
	}

	if (IsReturn_)
	{
		transform_.position_.x--;
	}
	else
	{
		transform_.position_.x++;
	}
	if (starDelay_ >= MAX_STAR_DELAY)
	{
		starDelay_ = 0;
	}
	else if (starDelay_ > 0)
	{
		starDelay_++;
	}
}

//描画
void Bomb::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Bomb::Release()
{
}