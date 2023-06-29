#include "Star.h"
#include "Scene/PlayScene.h"
#include "Player.h"

#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
Star::Star(GameObject* parent)
	: GameObject(parent, "Star"),scale_(0.15f),timeMax_(60), rotateSpeed_(3.f), rimit_(10), gravity_(0.05f), rimitY(1.5f)
{
}

//������
void Star::Initialize()
{
	hModel_ = Model::Load("Model\\star_white.fbx");
	assert(hPict_ >= 0);

	//�����蔻��
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.75f);
	AddCollider(collision);

	transform_.position_.y = 5;
	transform_.scale_ = {scale_, scale_, scale_};
}

//�X�V
void Star::Update()
{
	transform_.rotate_.y += rotateSpeed_;

	if (time_ <= timeMax_)
	{
		time_++;
	}

	if (transform_.position_.y <= rimitY)
	{
		transform_.position_.y = rimitY;
	}
	else
	{
		transform_.position_.y -= gravity_;
	}

	if (!IsVisibled() && time_ >= timeMax_)
	{
		KillMe();
	}
}

//�`��
void Star::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::SetColor(hModel_, XMFLOAT4(1, 1, 0, 1));
	Model::Draw(hModel_);
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
		if (time_ >= rimit_ && IsVisibled())
		{
			Invisible();
			time_ = 0;
		}
	}
}