#include "Bomb.h"
#include "Engine/Model.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Player.h"
#include "Manager/BombEffect.h"

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
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.5f);
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

	BombEffect::BombEffect(transform_.position_);
	time++;

	data.position = transform_.position_;
	
	if (time >= 100)
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

	if (starTime_ >= 7)
	{
		starTime_ = 0;
	}
	else if (starTime_ > 0)
	{
		starTime_++;
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

void Bomb::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "EnemyBlue" || 
		pTarget->GetObjectName() == "EnemyGreen" ||
		pTarget->GetObjectName() == "EnemyRed" ||
		pTarget->GetObjectName() == "Fire")
	{
		pTarget->KillMe();
	}
}