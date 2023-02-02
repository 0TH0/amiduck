#include "TitleScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TitleScene::Initialize()
{
	hPict_ = Image::Load("Title\\TitleLogo.png");
	assert(hPict_ >= 0);

	hPictCh_ = Image::Load("Title\\title_ch.png");
	assert(hPictCh_ >= 0);
}

//�X�V
void TitleScene::Update()
{
	//�����L�[�������ꂽ��
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}

	//if (alpha_ >= 256)
	//{
	//	Is_ = true;
	//}
	//else if (alpha_ <= 0)
	//{
	//	Is_ = false;
	//}

	//if (Is_)
	//{
	//	alpha_ -= 5;
	//}
	//else
	//{
	//	alpha_ += 5;
	//}
}

//�`��
void TitleScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	Transform trans;
	trans.position_.y = -0.75;

	Image::SetTransform(hPictCh_, trans);
	Image::Draw(hPictCh_);
	Image::FlashImage(hPictCh_, 5);
}

//�J��
void TitleScene::Release()
{
}
