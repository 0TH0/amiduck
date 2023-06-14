#include "StartScene.h"
#include "../Engine/Image.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"

//�R���X�g���N�^
StartScene::StartScene(GameObject* parent)
	: GameObject(parent, "StartScene")
{
}

//������
void StartScene::Initialize()
{
	Camera::SetDefault();

	hPict_[0] = Image::Load("Image\\start.png");
	assert(hPict_[0] >= 0);
}

//�X�V
void StartScene::Update()
{
}

//�`��
void StartScene::Draw()
{
	Image::SetTransform(hPict_[0], transform_);
	Image::Draw(hPict_[0]);
	Image::FadeoutImage(hPict_[0]);
}

//�J��
void StartScene::Release()
{
}