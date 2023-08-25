#include "TitleScene.h"
#include "../Engine/Image.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"
#include "../Engine/UI.h"
#include "../Image/Board.h"
#include "../Manager/ClickAudio.h"

namespace
{
	static SceneManager* pSceneManager;
	static UI* pUI[(int)TitleScene::UIName::UI_MAX];
	static Board* pBoard;
}

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScne"), UIName_()
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

	pBoard = Instantiate<Board>(this);

	//UIの位置
	pUI[(int)UIName::PLAY]->SetPosition(0.4f, -0.4f, 0);
	pUI[(int)UIName::TUTORIAL]->SetPosition(-0.4f, -0.4f, 0);
	pUI[(int)UIName::CHAR]->SetPosition(0, -0.5f, 0);

	ClickAudio::Initialize();
}

//更新
void TitleScene::Update()
{
	if (Input::IsMouseButtonDown(Input::LEFT))
	{
		pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TUTORIAL);

		ClickAudio::ClickAudio();
	}

	//プレイ画面
	if (Image::IsHitCursor(pUI[(int)UIName::PLAY]->GetHandle()))
	{
		UIName_ = UIName::PLAY;
	}
	else
	{
		if(UIName_ == UIName::PLAY) UIName_ = UIName::UI_MAX;
	}

	//チュートリアル画面
	if (Image::IsHitCursor(pUI[(int)UIName::TUTORIAL]->GetHandle()))
	{
		UIName_ = UIName::TUTORIAL;
	}
	else
	{
		if (UIName_ == UIName::TUTORIAL) UIName_ = UIName::UI_MAX;
	}
}

//描画
void TitleScene::Draw()
{
	//ボード
	pBoard->BoardDraw();
	//タイトル
	for (int i = (int)TitleScene::UIName::TITLE; i < (int)TitleScene::UIName::UI_MAX; i++)
	{
		Image::Draw(pUI[i]->GetHandle());
	}

	//文字を点滅させる
	Image::FlashImage(pUI[(int)UIName::CHAR]->GetHandle());
}

//開放
void TitleScene::Release()
{
}
