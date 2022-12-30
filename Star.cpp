#include "Star.h"
#include "PlayScene.h"
#include "Player.h"

#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
Star::Star(GameObject* parent)
	: GameObject(parent, "Star")
{
}

//������
void Star::Initialize()
{
	hModel_ = Model::Load("Star\\star.fbx");
	assert(hPict_ >= 0);

	//�����蔻��
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
	AddCollider(collision);

	transform_.scale_ = XMFLOAT3(0.1, 0.1, 0.1);
}

//�X�V
void Star::Update()
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

	RayCastData rDog;
	Camera::CalcScreenToWorld(rDog);
	Model::RayCast(hModel_, &rDog);

	if (rDog.hit)
	{
		transform_.position_.y++;
	}
}

//�`��
void Star::Draw()
{
	Model::SetTransform(hModel_, transform_);

	if (IsVisibled())
	{
		Model::Draw(hModel_);
	}
}

//�J��
void Star::Release()
{
}

void Star::OnCollision(GameObject* pTarget)
{
	//�G�ɓ�������
	if (pTarget->GetObjectName() == "Player")
	{
		Player* pPlayer = (Player*)FindObject("Player");

		if (IsVisibled())
		{
			//pPlayer->PlusStarCount(1);
		}

		Invisible();
		IsHit_ = true;
	}
}