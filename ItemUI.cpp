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

//コンストラクタ
ItemUI::ItemUI(GameObject* parent)
	: GameObject(parent, "ItemUI")
{
	for (int i = 0; i < 5; i++)
	{
		hPict_[i] = -1;
	}
	
	alpha_ = 0;
	pItemBox_ = nullptr;
}

//初期化
void ItemUI::Initialize()
{
	hPict_[0] = Image::Load("UI\\ItemFrame.png");
	assert(hPict_[0] >= 0);

	hPict_[1] = Image::Load("UI\\apple.png");
	assert(hPict_[1] >= 0);

	hPict_[2] = Image::Load("UI\\komatsuna.png");
	assert(hPict_[2] >= 0);

	hPict_[3] = Image::Load("UI\\woodUI.png");
	assert(hPict_[3] >= 0);
}

//更新
void ItemUI::Update()
{
}

//描画
void ItemUI::Draw()
{
	for (int i = 0; i < 2; i++)
	{
		if (i > 0)
		{
			transform_.position_ = XMFLOAT3(0.85f, 0.75f, 0);
		}
		else
		{
			transform_.position_ = XMFLOAT3(0.85f, -0.75f, 0);
		}
		Image::SetTransform(hPict_[0], transform_);
		Image::Draw(hPict_[0]);
	}

	Stage* pStage = (Stage*)FindObject("Stage");
	transform_.position_ = XMFLOAT3(0.85f, -0.75f, 0);

	if (pStage->GetWoodCoolTime() >= 300)
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
	Image::SetTransform(hPict_[3], tra);
	Image::Draw(hPict_[3]);
}

void ItemUI::DrawUI(Transform tra)
{
	//Image::SetTransform(hPict_[1], trs);
	//Image::Draw(hPict_[1]);

	Image::SetTransform(hPict_[2], tra);
	Image::Draw(hPict_[2]);
}