#include "ItemUI.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/GameObject.h"
#include "PlayScene.h"
#include "Player.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"

//コンストラクタ
ItemUI::ItemUI(GameObject* parent)
	: GameObject(parent, "ItemUI")
{
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
}

//更新
void ItemUI::Update()
{
}

//描画
void ItemUI::Draw()
{
	transform_.position_ = XMFLOAT3(0.85, 0.75, 0);
	Image::SetTransform(hPict_[0], transform_);
	Image::Draw(hPict_[0]);
}

//開放
void ItemUI::Release()
{
}

void ItemUI::DrawUI(Transform trs)
{
	//Image::SetTransform(hPict_[1], trs);
	//Image::Draw(hPict_[1]);

	Image::SetTransform(hPict_[2], trs);
	Image::Draw(hPict_[2]);
}