#include "ItemUI.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/GameObject.h"
#include "PlayScene.h"
#include "Player.h"
#include "Stage.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"
#include "Engine/Math.h"

//コンストラクタ
ItemUI::ItemUI(GameObject* parent)
	: GameObject(parent, "ItemUI")
{
	for (int i = 0; i < 5; i++)
	{
		hItemPict_[i] = -1;
	}
	
	alpha_ = 0;
	pItemBox_ = nullptr;
	item_ = Item::ITEM_MAX;
	woodCount_ = (int)WoodCount::THREE;
}

//初期化
void ItemUI::Initialize()
{
	hPict_= Image::Load("UI\\ItemFrame.png");
	assert(hPict_ >= 0);

	hPictWood_ = Image::Load("UI\\woodUI.png");
	assert(hPictWood_>= 0);

	//モデルデータのロード
	std::string fileName[] =
	{
		"UI\\bomb.png",
		"UI\\ball.png",
		"UI\\wing.png",
	};

	for (int i = (int)Item::BOMB; i < (int)Item::ITEM_MAX; i++)
	{
		std::string fn = fileName[i];
		hItemPict_[i] = Image::Load(fn);
		assert(hItemPict_[i] >= 0);
	}
}

//更新
void ItemUI::Update()
{
	//アイテムを拾ったら１回だけ実行
	if (IsItem_)
	{
		item_ = (Item)Math::RandInt((int)Item::BOMB, (int)Item::ITEM_MAX - 1);
		IsItem_ = false;
	}

	if (woodCount_ < 3)
	{
		if (woodCoolTime_ >= 300)
		{
			woodCoolTime_ = 0;
			PluswoodCount();
		}
		else
		{
			woodCoolTime_++;
		}
	}
}

//描画
void ItemUI::Draw()
{
	transform_.position_ = XMFLOAT3(0.85f, 0.75f, 0);

	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	Stage* pStage = (Stage*)FindObject("Stage");
	transform_.position_ = XMFLOAT3(0.5f, -0.75f, 0);

	if (woodCount_ > 0)
	{
		DrawWoodUI(transform_);
	}
}

//開放
void ItemUI::Release()
{
}

void ItemUI::DrawWoodUI(Transform tra)
{
	tra.scale_ = XMFLOAT3(0.75f, 0.75f, 0.75f);
	for (int i = 0; i < woodCount_; i++)
	{
		if(i != 0) tra.position_.x += 0.2f;
		Image::SetTransform(hPictWood_, tra);
		Image::Draw(hPictWood_);
	}
}

void ItemUI::DrawItem(Transform tra)
{
	Image::SetTransform(hItemPict_[(int)item_], tra);
	Image::Draw(hItemPict_[(int)item_]);
}