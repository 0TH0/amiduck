#include "ItemUI.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/GameObject.h"
#include "PlayScene.h"
#include "Player.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"

//�R���X�g���N�^
ItemUI::ItemUI(GameObject* parent)
	: GameObject(parent, "ItemUI")
{
}

//������
void ItemUI::Initialize()
{
	hPict_[0] = Image::Load("UI\\ItemFrame.png");
	assert(hPict_[0] >= 0);
}

//�X�V
void ItemUI::Update()
{
	//alpha_ -= 1.5;
}

//�`��
void ItemUI::Draw()
{
	transform_.position_ = XMFLOAT3(0.85, 0.75, 0);
	Image::SetTransform(hPict_[0], transform_);
	Image::Draw(hPict_[0]);
}

//�J��
void ItemUI::Release()
{
}