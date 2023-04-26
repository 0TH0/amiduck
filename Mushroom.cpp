#include "Mushroom.h"
#include "Engine/Model.h"

EmitterData data;
//�R���X�g���N�^
Mushroom::Mushroom(GameObject* parent)
	: GameObject(parent, "Mushroom"), hModel_(-1)
{
}

//������
void Mushroom::Initialize()
{
	hModel_ = Model::Load("Model\\fire\\fireball.fbx");
	assert(hModel_ >= 0);

	transform_.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5f);

	//�����蔻��
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 1.f);
	//AddCollider(collision);

	pParticle_ = Instantiate<Particle>(this);

	//��
	data.textureFileName = "Image\\Cloud.png";
	data.positionErr = XMFLOAT3(0.1, 0, 0.1);
	data.delay = 0;
	data.number = 1;
	data.lifeTime = 60;
	//data.gravity = -0.002f;
	data.dir = XMFLOAT3(0, 1, 0);
	data.dirErr = XMFLOAT3(0, 0, 0);
	data.speed = 0.01f;
	data.speedErr = 0.0;
	data.size = XMFLOAT2(1.5, 1.5);
	data.sizeErr = XMFLOAT2(0.4, 0.4);
	data.scale = XMFLOAT2(1.01, 1.01);
	data.color = XMFLOAT4(1, 1, 0, 1);
	data.deltaColor = XMFLOAT4(0, -0.03, 0, -0.02);
}

//�X�V
void Mushroom::Update()
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
	data.position = transform_.position_;
	pParticle_->Start(data);
}

//�`��
void Mushroom::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Mushroom::Release()
{
}