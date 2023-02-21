#include "Line.h"
#include "Engine/Image.h"

//�R���X�g���N�^
Line::Line(GameObject* parent)
	: GameObject(parent, "Line")
{
}

//������
void Line::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("Image\\line_white.png");
	assert(hPict_ >= 0);
}

//�X�V
void Line::Update()
{
	time_++;
}

//�`��
void Line::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::SetAlpha(hPict_, alpha_);
	Image::Draw(hPict_);
}

//�J��
void Line::Release()
{
}
