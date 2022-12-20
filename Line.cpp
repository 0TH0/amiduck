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

	if (time_ > 50)
	{
		KillMe();
	}
	else if (time_ % 10 == 0)
	{
		alpha_ = 64;
	}
	else if (time_ % 5 == 0)
	{
		alpha_ = 128;
	}
}

//�`��
void Line::Draw()
{
	Image::SetTransform(hPict_, transform_);
	//Image::SetColor(hPict_, 0, 0, 0);
	Image::SetAlpha(hPict_, alpha_);
	Image::Draw(hPict_);
}

//�J��
void Line::Release()
{
}
