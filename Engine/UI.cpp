#include "UI.h"
#include "Image.h"
#include "Input.h"

//�R���X�g���N�^
UI::UI(GameObject* parent)
	: GameObject(parent, "UI"),hPict_(-1),shouldUseHitCursor_(false)
{
}

//������
void UI::Initialize()
{
	//�摜�����[�h
	Load(fileName_);
}

//�X�V
void UI::Update()
{
	//�J�[�\������������������g����
	if (shouldUseHitCursor_)
	{
		//�J�[�\�����摜�ɓ������Ă�����
		if (Image::IsHitCursor(hPict_))
		{
			Image::SetColor(hPict_, 0.7f, 0.7f, 0.7f);
		}
		else
		{
			Image::SetColor(hPict_, 1, 1, 1);
		}
	}
}

//�`��
void UI::Draw()
{
	Image::SetTransform(hPict_, transform_);
}

//�J��
void UI::Release()
{
}

void UI::Load(std::string fileName)
{
	fileName_ = fileName;
	hPict_ = Image::Load(fileName_);
}