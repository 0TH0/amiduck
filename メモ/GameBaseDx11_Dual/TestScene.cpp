#include "TestScene.h"
#include "Engine/Model.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene"), hModel_(-1)
{
}

//������
void TestScene::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Oden.fbx");
	assert(hModel_ >= 0);
}

//�X�V
void TestScene::Update()
{
}

//�`��
void TestScene::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void TestScene::Release()
{
}
