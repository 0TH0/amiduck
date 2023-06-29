#include "PlaySceneGuide.h"
#include "../Engine/UI.h"
#include "../Engine/Image.h"

namespace
{
	UI* pUI;
}

//�R���X�g���N�^
PlaySceneGuide::PlaySceneGuide(GameObject* parent)
	: GameObject(parent, "PlaySceneGuide")
{
}

//������
void PlaySceneGuide::Initialize()
{
	pUI = Instantiate<UI>(this);
	pUI->Load("Image\\start.png");
}

//�X�V
void PlaySceneGuide::Update()
{
}

//�`��
void PlaySceneGuide::Draw()
{
	Image::Draw(pUI->GetHandle());
	Image::FadeoutImage(pUI->GetHandle());
}

//�J��
void PlaySceneGuide::Release()
{
}
