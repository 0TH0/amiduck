#include "ResultScene.h"
#include "../Engine/Image.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"
#include "../Engine/UI.h"
#include "../Observer/ResultObserver.h"
#include "../Image/Board.h"
#include "../Manager/AudioManager.h"

namespace
{
	static SceneManager* pSceneManager;
	static UI* pUI[(int)ResultScene::UIName::UI_MAX];
	static Board* pBoard;
}

//コンストラクタ
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "TitleScne"), UIName_()
{
}

//初期化
void ResultScene::Initialize()
{
	std::string resultStr = "";

	//勝敗によって変える
	if (ResultObserver::GetIsWin())
	{
		resultStr = "Clear\\win.png";
		AudioManager::WinAudio();
	}
	else
	{
		resultStr = "Clear\\lose.png";
		AudioManager::LoseAudio();
	}
	assert(resultStr != "");

	std::string filename[] = {
		"Clear\\finish.png",
		"Clear\\retry.png",
		"Clear\\BackTitle.png",
		resultStr,
	};

	float scale = 0.8f;
	for (int i = (int)ResultScene::UIName::FINISH; i < (int)ResultScene::UIName::UI_MAX; i++)
	{
		std::string fn = filename[i];
		pUI[i] = Instantiate<UI>(this);
		pUI[i]->Load(fn);
		pUI[i]->SetScale(scale * 1.1f, scale, scale);
	};

	for (int i = (int)ResultScene::UIName::FINISH; i < (int)ResultScene::UIName::UI_MAX - 1; i++)
	{
		pUI[i]->SetShouldUseHitCursor(true);
	};

	//UIの位置
	pUI[(int)UIName::RESULT]->SetPosition(0, 0.175f, 0);

	pUI[(int)UIName::RETRY]->SetPosition(0, 0.15, 0);
	pUI[(int)UIName::BACK_TITLE]->SetPosition(0, -0.25f, 0);
	pUI[(int)UIName::FINISH]->SetPosition(0, -0.65, 0);

	pBoard = Instantiate<Board>(this);
}

//更新
void ResultScene::Update()
{
	if (Input::IsMouseButtonDown(Input::LEFT))
	{
		switch (UIName_)
		{
		case ResultScene::UIName::UI_MAX:
			break;
		case ResultScene::UIName::FINISH:
			PostQuitMessage(0);
			break;
		case ResultScene::UIName::RETRY:
			pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_PLAY);
			break;
		case ResultScene::UIName::BACK_TITLE:
			pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_TITLE);
			break;
		}
	}

	//プレイ画面
	if (Image::IsHitCursor(pUI[(int)UIName::FINISH]->GetHandle()))
	{
		UIName_ = UIName::FINISH;
	}
	else
	{
		if (UIName_ == UIName::FINISH) UIName_ = UIName::UI_MAX;
	}

	//チュートリアル画面
	if (Image::IsHitCursor(pUI[(int)UIName::RETRY]->GetHandle()))
	{
		UIName_ = UIName::RETRY;
	}
	else
	{
		if (UIName_ == UIName::RETRY) UIName_ = UIName::UI_MAX;
	}

	//タイトルへ
	if (Image::IsHitCursor(pUI[(int)UIName::BACK_TITLE]->GetHandle()))
	{
		UIName_ = UIName::BACK_TITLE;
	}
	else
	{
		if (UIName_ == UIName::BACK_TITLE) UIName_ = UIName::UI_MAX;
	}
}

//描画
void ResultScene::Draw()
{
	//ボード
	pBoard->BoardDraw();
	//勝敗と各種ボタン
	for (int i = (int)ResultScene::UIName::FINISH; i < (int)ResultScene::UIName::UI_MAX; i++)
	{
		Image::Draw(pUI[i]->GetHandle());
	}
}

//開放
void ResultScene::Release()
{
}