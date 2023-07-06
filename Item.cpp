#include "Item.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/GameObject.h"
#include "Scene/PlayScene.h"
#include "Player.h"
#include "Stage.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"

//コンストラクタ
Item::Item(GameObject* parent)
	: GameObject(parent, "Item"), IsItem_(false),hPictWood_(0),hPict_(0),woodCoolTime_(0)
{
	for (int i = (int)ItemNum::BOMB; i < (int)ItemNum::ITEM_MAX; i++)
	{
		hItemPict_[i] = -1;
	}
	
	alpha_ = 0;
	pItemBox_ = nullptr;
	item_ = ItemNum::ITEM_MAX;
	woodCount_ = (int)WoodCount::THREE;
}

//初期化
void Item::Initialize()
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

	for (int i = (int)ItemNum::BOMB; i < (int)ItemNum::ITEM_MAX; i++)
	{
		std::string fn = fileName[i];
		hItemPict_[i] = Image::Load(fn);
		assert(hItemPict_[i] >= 0);
	}
}

//更新
void Item::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");
	//アイテムを拾ったら１回だけ実行
	if (!(pPlayer->GetHasItem()))
	{
		item_ = (ItemNum)RandInt((int)ItemNum::BOMB, (int)ItemNum::ITEM_MAX - 1);
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
void Item::Draw()
{
	transform_.position_ = XMFLOAT3(0.85f, 0.75f, 0);

	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	transform_.position_ = XMFLOAT3(0.5f, -0.75f, 0);

	if (woodCount_ > ZERO)
	{
		DrawWoodUI(transform_);
	}
}

//開放
void Item::Release()
{
}

void Item::DrawWoodUI(Transform tra)
{
	tra.scale_ = XMFLOAT3(0.75f, 0.75f, 0.75f);
	for (int i = 0; i < woodCount_; i++)
	{
		if(i != 0) tra.position_.x += 0.2f;
		Image::SetTransform(hPictWood_, tra);
		Image::Draw(hPictWood_);
	}
}

void Item::DrawItem()
{
	transform_.position_ = XMFLOAT3(0.85f, 0.75f, 0);
	Image::SetTransform(hItemPict_[(int)item_], transform_);
	Image::Draw(hItemPict_[(int)item_]);
}