#include "Sky.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

//�R���X�g���N�^
Sky::Sky(GameObject* parent)
	: GameObject(parent, "Sky"), hPict_(-1)
{
}

//������
void Sky::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("Sky.png");
	assert(hPict_ >= 0);
}

//�X�V
void Sky::Update()
{
}

//�`��
void Sky::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void Sky::Release()
{
}

