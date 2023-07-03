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

//�R���X�g���N�^
ItemBox::ItemBox(GameObject* parent)
	: GameObject(parent, "ItemBox"),IsHit_(false),hModel_(-1)
{
}

//������
void ItemBox::Initialize()
{
	hModel_ = Model::Load("Model\\itemBox.fbx");
	assert(hModel_ >= 0);

	//�����蔻��
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
	AddCollider(collision);

	transform_.scale_ = { 1.5f,1.5f,1.5f };
}

//�X�V
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

//�`��
void ItemBox::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	Player* pPlayer = (Player*)FindObject("Player");

	//�A�C�e���{�b�N�X�ɓ������ăv���C���[���A�C�e���������Ă���Ƃ�
	if ((pPlayer->GetHasItem()))
	{
		Transform trans;
		trans.position_ = XMFLOAT3(0.85, 0.75, 0);
		Item* pItem = (Item*)FindObject("Item");
		pItem->DrawItem(trans);
	}
}

//�J��
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