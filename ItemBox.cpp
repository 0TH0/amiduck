#include "ItemBox.h"
#include "Scene/PlayScene.h"
#include "Player.h"
#include "Item.h"
#include "Manager/ItemBoxEffect.h"
#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

//コンストラクタ
ItemBox::ItemBox(GameObject* parent)
	: GameObject(parent, "ItemBox"),IsHit_(false),hModel_(-1)
{
}

//初期化
void ItemBox::Initialize()
{
	hModel_ = Model::Load("Model\\itemBox.fbx");
	assert(hModel_ >= 0);

	//当たり判定
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
	AddCollider(collision);

	transform_.scale_ = { 1.5f,1.5f,1.5f };
}

//更新
void ItemBox::Update()
{
	transform_.rotate_.y += 3;

	if (IsHit_)
	{
		time_++;
	}

	if (time_ >= 600)
	{
		Visible();
		IsHit_ = false;
		time_ = 0;
	}
}

//描画
void ItemBox::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	Player* pPlayer = (Player*)FindObject("Player");

	//アイテムボックスに当たってプレイヤーがアイテムを持っているとき
	if ((pPlayer->GetHasItem()))
	{
		Transform trans;
		trans.position_ = XMFLOAT3(0.85, 0.75, 0);
		Item* pItem = (Item*)FindObject("Item");
		pItem->DrawItem(trans);
	}
}

//開放
void ItemBox::Release()
{
}

void ItemBox::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Player")
	{
		Player* pPlayer = (Player*)FindObject("Player");

		if (IsVisibled())
		{
			ItemBoxEffect::TakeItemBoxEffect(transform_.position_);
			pPlayer->SetHasItem(true);
		}
		Invisible();
		IsHit_ = true;
	}
}