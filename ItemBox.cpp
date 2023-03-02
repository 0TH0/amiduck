#include "ItemBox.h"
#include "PlayScene.h"
#include "Player.h"
#include "ItemUI.h"

#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
ItemBox::ItemBox(GameObject* parent)
	: GameObject(parent, "ItemBox")
{
}

//������
void ItemBox::Initialize()
{
	hModel_ = Model::Load("Model\\itemBox.fbx");
	assert(hPict_ >= 0);

	//�����蔻��
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
	AddCollider(collision);

	pParticle_ = Instantiate<Particle>(this);
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

	if (IsVisibled())
	{
		Model::Draw(hModel_);
	}

	Player* pPlayer = (Player*)FindObject("Player");

	//�A�C�e���{�b�N�X�ɓ������ăv���C���[���A�C�e���������Ă��Ȃ��Ƃ�
	if ((pPlayer->GetHasItem()))
	{
		Transform trans;
		trans.position_ = XMFLOAT3(0.85, 0.75, 0);
		ItemUI* pItemUI = (ItemUI*)FindObject("ItemUI");
		pItemUI->DrawItem(trans);
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
			QuestionEffect();
			pPlayer->SetHasItem(true);
			//�A�C�e������肵�����̏���
			ItemUI* pItemUI = (ItemUI*)FindObject("ItemUI");
			pItemUI->SetIsItem(true);
		}
		Invisible();
		IsHit_ = true;
	}
}

void ItemBox::QuestionEffect()
{
	EmitterData data;
	data.textureFileName = "Image\\question_white.png";
	data.position = transform_.position_;
	data.delay = 0;
	data.number = 80;
	data.lifeTime = 100;
	data.positionErr = XMFLOAT3(0.4, 0, 0.4);
	data.dir = XMFLOAT3(0, 1, 0);
	data.dirErr = XMFLOAT3(90, 90, 90);
	data.speed = 0.25f;
	data.speedErr = 1;
	data.accel = 0.93;
	data.size = XMFLOAT2(0.4, 0.4);
	data.sizeErr = XMFLOAT2(0.4, 0.4);
	data.scale = XMFLOAT2(1, 1);
	data.color = XMFLOAT4(1, 1, 1, 1);
	data.deltaColor = XMFLOAT4(0, 0, 0, 0);
	data.gravity = 0.003f;
	pParticle_->Start(data);
}