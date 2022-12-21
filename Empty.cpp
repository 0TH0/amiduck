#include "Empty.h"
#include "TestScene.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Empty::Empty(GameObject* parent)
	: GameObject(parent, "TestScene")
{
}

//������
void Empty::Initialize()
{
	hModel_ = Model::Load("Empty.fbx");
	assert(hModel_ >= 0);
}

//�X�V
void Empty::Update()
{
}

//�`��
void Empty::Draw()
{
	//Model::SetTransform(hModel_, transform_);
	//Model::Draw(hModel_);
}

//�J��
void Empty::Release()
{
}
