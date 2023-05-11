#include "UI.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

//�R���X�g���N�^
UI::UI(GameObject* parent)
	: GameObject(parent, "UI"),hPict_(-1)
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