#include "TitleScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "UI.h"

SceneManager* pSceneManager;
UI* pUI[(int)TitleScene::UIName::UI_MAX];

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScne"), btState_()
{
}

//初期化
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

//更新
void TitleScene::Update()
{
	if (Input::IsMouseButtonDown(0))
	{
		switch (btState_)
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
	switch (btState_)
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

	//プレイ画面
	if (Image::IsHitCursor(pUI[(int)UIName::PLAY]->GetHandle()))
	{
		btState_ = UIName::PLAY;
	}
	else
	{
		if(btState_ == UIName::PLAY) btState_ = UIName::UI_MAX;
	}

	//チュートリアル画面
	if (Image::IsHitCursor(pUI[(int)UIName::Tutorial]->GetHandle()))
	{
		btState_ = UIName::Tutorial;
	}
	else
	{
		if (btState_ == UIName::Tutorial) btState_ = UIName::UI_MAX;
	}
}

//描画
void TitleScene::Draw()
{
	//UIの位置
	pUI[(int)UIName::PLAY]->SetPosition(0.4f, -0.4f, 0);
	pUI[(int)UIName::Tutorial]->SetPosition(-0.4f, -0.4f, 0);
	pUI[(int)UIName::Char]->SetPosition(0, -0.8f, 0);

	//文字を点滅させる
	Image::FlashImage(pUI[(int)UIName::Char]->GetHandle());
}

//開放
void TitleScene::Release()
{
}
