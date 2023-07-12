#include "TitleScene.h"
#include "../Engine/Image.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"
#include "../Engine/UI.h"

static SceneManager* pSceneManager;
static UI* pUI[(int)TitleScene::UIName::UI_MAX];

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScne"), UIName_()
{
}

//������
void TitleScene::Initialize()
{
	std::string filename[] = {
		"Title\\playBt.png",
		"Title\\tutorialBt.png",
		"Title\\TitleLogo.png",
		"Title\\title_ch.png"
	};

	for (int i = (int)TitleScene::UIName::PLAY; i < (int)TitleScene::UIName::UI_MAX; i++)
	{
		std::string fn = filename[i];
		pUI[i] = Instantiate<UI>(this);
		pUI[i]->Load(fn);
	};

	//UI�̈ʒu
	pUI[(int)UIName::PLAY]->SetPosition(0.4f, -0.4f, 0);
	pUI[(int)UIName::TUTORIAL]->SetPosition(-0.4f, -0.4f, 0);
	pUI[(int)UIName::CHAR]->SetPosition(0, -0.5f, 0);
}

//�X�V
void TitleScene::Update()
{
	if (Input::IsMouseButtonDown(Input::LEFT))
	{
		pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);

		switch (UIName_)
		{
		case TitleScene::UIName::UI_MAX:
			break;
		case TitleScene::UIName::PLAY:
			pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_PLAY);
			break;
		}
	}

	//�v���C���
	if (Image::IsHitCursor(pUI[(int)UIName::PLAY]->GetHandle()))
	{
		UIName_ = UIName::PLAY;
	}
	else
	{
		if(UIName_ == UIName::PLAY) UIName_ = UIName::UI_MAX;
	}

	//�`���[�g���A�����
	if (Image::IsHitCursor(pUI[(int)UIName::TUTORIAL]->GetHandle()))
	{
		UIName_ = UIName::TUTORIAL;
	}
	else
	{
		if (UIName_ == UIName::TUTORIAL) UIName_ = UIName::UI_MAX;
	}
}

//�`��
void TitleScene::Draw()
{
	for (int i = (int)TitleScene::UIName::TITLE; i < (int)TitleScene::UIName::UI_MAX; i++)
	{
		Image::Draw(pUI[i]->GetHandle());
	}

	//������_�ł�����
	Image::FlashImage(pUI[(int)UIName::CHAR]->GetHandle());
}

//�J��
void TitleScene::Release()
{
}
