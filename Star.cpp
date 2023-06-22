#include "Star.h"
#include "Scene/PlayScene.h"
#include "Player.h"
#include "Manager/StarEffect.h"
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
	hModel_ = Model::Load("Model\\Heart.fbx");
	assert(hPict_ >= 0);

	//�����蔻��
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
	AddCollider(collision);

	transform_.scale_ = { 2,2,2 };
}

//�X�V
void Star::Update()
{
	transform_.rotate_.y += 3;
	
	if (time_ <= 60)
	{
		time_++;
	}

	if (transform_.position_.y <= 1.25f)
	{
		transform_.position_.y = 1.25f;
	}
	else
	{
		transform_.position_.y -= 0.05f;
	}
	if (!IsVisibled() && time_ >= 60)
	{
		KillMe();
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
	if (pTarget->GetObjectName() == "Player" || pTarget->GetObjectName() == "Enemy")
	{
		if (time_ >= 10 && IsVisibled())
		{
			Invisible();
			StarEffect::TakeStarEffect(transform_.position_);
			time_ = 0;
		}
	}
}