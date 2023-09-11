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
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 3.f);
	AddCollider(collision);

	transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35);

	transform_.rotate_ = XMFLOAT3(0, 0, 0);
}

XMVECTOR player;
XMVECTOR mouse;
//更新
void Bomb::Update()
{
	if (Input::IsKey(DIK_O))
	{
		Player* pPlayer = (Player*)FindObject("Player");
		playerPos_ = pPlayer->GetPosition();
		playerPos_.y = 3;
		transform_.position_ = playerPos_;
		player = XMLoadFloat3(&playerPos_);


		//初期位置はプレイヤーの位置のｙ＋１
		pStage = (Stage*)FindObject("Stage");
		mousePos_ = XMFLOAT3(pStage->GetMousePos().x, 3, pStage->GetMousePos().z);

		mouse = XMLoadFloat3(&mousePos_);
	}
	else
	{
		XMVECTOR Root = (mouse - player);

		//正規化する
		Root = XMVector3Normalize(Root);//ベクトルの長さを１にして

		XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) + Root);
		transform_.position_.y = 3;
	}
	//transform_.rotate_.x += 5;
	//time_++;
	//
	//if (time_ >= MAX_TIME)
	//{
	//	KillMe();
	//}
	//if (IsReturn_)
	//{
	//	transform_.position_.x--;
	//}
	//else
	//{
	//	transform_.position_.x++;
	//}
	//if (starDelay_ >= MAX_STAR_DELAY)
	//{
	//	starDelay_ = 0;
	//}
	//else if (starDelay_ > 0)
	//{
	//	starDelay_++;
	//}
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