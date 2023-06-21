#include "Fire.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Fire::Fire(GameObject* parent)
	: GameObject(parent, "Fire"), hModel_(-1)
{
}

//������
void Fire::Initialize()
{
	hModel_ = Model::Load("Model\\fire\\fireball.fbx");
	assert(hModel_ >= 0);

	transform_.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5f);

	//�����蔻��
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 2.f);
	AddCollider(collision);
}

//�X�V
void Fire::Update()
{
	//��񂾂����s
	if (!first_)
	{
		trans.position_ = transform_.position_;
		first_ = true;
	}

	//��
	transform_.position_ = Transform::RotateAround(trans.position_, 10.f, 2.f, right_);
	//transform_.position_ =
	//	XMFLOAT3(
	//		Transform::RotateAround(trans.position_, (dir += rotateSpeed), 2.f, right_).x,
	//		transform_.position_.y += 0.05f,
	//		Transform::RotateAround(trans.position_, (dir += rotateSpeed), 2.f, right_).z);
	transform_.rotate_.y += 5;

	//���̍X�V
	//data.position = transform_.position_;
	//pParticle_->Start(data);
}

//�`��
void Fire::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Fire::Release()
{
}