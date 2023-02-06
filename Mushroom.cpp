#include "Mushroom.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Mushroom::Mushroom(GameObject* parent)
	: GameObject(parent, "Mushroom"), hModel_(-1)
{
}

//������
void Mushroom::Initialize()
{
	hModel_ = Model::Load("Model\\Player\\egg.fbx");
	assert(hModel_ >= 0);

	transform_.position_ = XMFLOAT3(29, 1, 32);
	transform_.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5f);

	//�����蔻��
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
	AddCollider(collision);
}

//�X�V
void Mushroom::Update()
{
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