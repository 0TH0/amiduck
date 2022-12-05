#include "Coin.h"
#include "PlayScene.h"
#include "Player.h"

#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

//�R���X�g���N�^
Coin::Coin(GameObject* parent)
	: GameObject(parent, "Coin")
{
}

//������
void Coin::Initialize()
{
	hModel_ = Model::Load("Coin\\coin.fbx");
	assert(hPict_ >= 0);

	//�����蔻��
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
	AddCollider(collision);
}

//�X�V
void Coin::Update()
{
	transform_.rotate_.y += 3;

	if (IsHit_)
	{
		time_++;
	}

	if (time_ >= 300)
	{
		Visible();
		IsHit_ = false;
		time_ = 0;
	}
}

//�`��
void Coin::Draw()
{
	Model::SetTransform(hModel_, transform_);

	if (IsVisibled())
	{
		Model::Draw(hModel_);
	}
}

//�J��
void Coin::Release()
{
}

void Coin::OnCollision(GameObject* pTarget)
{
	//�G�ɓ�������
	if (pTarget->GetObjectName() == "Player")
	{
		Player* pPlayer = (Player*)FindObject("Player");

		if (IsVisibled())
		{
			pPlayer->PlusCoinCount(1);
		}

		Invisible();
		IsHit_ = true;
	}
}