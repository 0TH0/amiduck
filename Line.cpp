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

	Image::SetTransform(hPict_, transform_);
}

//�X�V
void Line::Update()
{
	if (Image::GetTime(hPict_) >= ONE_SECOND)
	{
		KillMe();
	}
}

//�`��
void Line::Draw()
{
	Image::Draw(hPict_);
	Image::FlashImage2(hPict_);
}

//�J��
void Line::Release()
{
}
