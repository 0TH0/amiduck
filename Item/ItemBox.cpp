#include "ItemBox.h"
#include "../Scene/PlayScene.h"
#include "../Player/Player.h"
#include "Item.h"
#include "../Manager/ItemBoxEffect.h"
#include "../Engine/Model.h"
#include "../Engine/Image.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"

namespace
{
	static const XMFLOAT3 SCALE = { 1.5f, 1.5f, 1.5f };
	static const float RADIUS = 0.75f;
	static const float ROTATE_SPEED = 3.f;
	static const int COOL_TIME = 900;
}

//�R���X�g���N�^
ItemBox::ItemBox(GameObject* parent)
	: GameObject(parent, "ItemBox"),IsHit_(false),hModel_(-1)
{
}

//������
void ItemBox::Initialize()
{
	hModel_ = Model::Load("Model\\itemBox.fbx");
	assert(hModel_ >= ZERO);

	//�����蔻��
	SphereCollider* collision = new SphereCollider(XMFLOAT3(ZERO, ZERO, ZERO), RADIUS);
	AddCollider(collision);

	transform_.scale_ = SCALE;
}

//�X�V
void ItemBox::Update()
{
	transform_.rotate_.y += ROTATE_SPEED;

	if (IsHit_)
	{
		time_++;
	}

	if (time_ >= COOL_TIME)
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
		Item* pItem = (Item*)FindObject("Item");
		pItem->DrawItem();
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
			//�G�t�F�N�g
			ItemBoxEffect::TakeItemBoxEffect(transform_.position_);
			pPlayer->SetHasItem(true);
		}
		Invisible();
		IsHit_ = true;
	}
}