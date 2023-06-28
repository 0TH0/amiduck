#include "Instructions.h"

#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

//�R���X�g���N�^
Instructions::Instructions(GameObject* parent)
	: GameObject(parent, "Instructions")
{
}

//������
void Instructions::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("Image\\Instruction.png");
	assert(hPict_ >= 0);
	transform_.position_ = XMFLOAT3(0, -0.95f, 0);
}

//�X�V
void Instructions::Update()
{
}

//�`��
void Instructions::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void Instructions::Release()
{
}