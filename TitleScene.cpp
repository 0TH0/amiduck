#include "TitleScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "UI.h"

SceneManager* pSceneManager;
UI* pUI[(int)TitleScene::UIName::UI_MAX];

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
}

//�X�V
void TitleScene::Update()
{
	if (Input::IsMouseButtonDown(0))
	{
		switch (UIName_)
		{
		case TitleScene::UIName::UI_MAX:
			break;
		case TitleScene::UIName::PLAY:
			pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_PLAY);
			break;
		case TitleScene::UIName::Tutorial:
			pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_TUTORIAL);
			break;
		}
	}
	switch (UIName_)
	{
	case TitleScene::UIName::UI_MAX:
		Image::SetColor(pUI[(int)UIName::Tutorial]->GetHandle());
		Image::SetColor(pUI[(int)UIName::PLAY]->GetHandle());
		break;
	case TitleScene::UIName::PLAY:
		Image::SetColor(pUI[(int)UIName::PLAY]->GetHandle(), 0.7f, 0.7f, 0.7f);
		Image::SetColor(pUI[(int)UIName::Tutorial]->GetHandle());
		break;
	case TitleScene::UIName::Tutorial:
		Image::SetColor(pUI[(int)UIName::Tutorial]->GetHandle(), 0.7f, 0.7f, 0.7f);
		Image::SetColor(pUI[(int)UIName::PLAY]->GetHandle());
		break;
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
	if (Image::IsHitCursor(pUI[(int)UIName::Tutorial]->GetHandle()))
	{
		UIName_ = UIName::Tutorial;
	}
	else
	{
		if (UIName_ == UIName::Tutorial) UIName_ = UIName::UI_MAX;
	}
}

//�`��
void TitleScene::Draw()
{
	//UI�̈ʒu
	pUI[(int)UIName::PLAY]->SetPosition(0.4f, -0.4f, 0);
	pUI[(int)UIName::Tutorial]->SetPosition(-0.4f, -0.4f, 0);
	pUI[(int)UIName::Char]->SetPosition(0, -0.8f, 0);

	//������_�ł�����
	Image::FlashImage(pUI[(int)UIName::Char]->GetHandle());
}

//�J��
void TitleScene::Release()
{
}
