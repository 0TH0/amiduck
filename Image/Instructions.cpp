#include "Instructions.h"
#include "../Engine/Image.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"

namespace
{
	static const XMFLOAT3 pos = { 0, -0.95f, 0 };
}

//�R���X�g���N�^
Instructions::Instructions(GameObject* parent)
	: GameObject(parent, "Instructions"),hPict_(-1)
{
}

//������
void Instructions::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("Image\\Instruction.png");
	assert(hPict_ >= ZERO);
	transform_.position_ = pos;
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