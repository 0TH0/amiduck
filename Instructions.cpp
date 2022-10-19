#include "Instructions.h"
#include "PlayScene.h"

#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

//�R���X�g���N�^
Instructions::Instructions(GameObject* parent)
	: GameObject(parent, "Instructions"), IsInstructions(false)
{
}

//������
void Instructions::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("Instructions.png");
	assert(hPict_ >= 0);
}

//�X�V
void Instructions::Update()
{
	if (Input::IsKey(DIK_K))
	{
		KillMe();
	}
}

//�`��
void Instructions::Draw()
{
	Image::SetAlpha(hPict_, 150);
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void Instructions::Release()
{
}