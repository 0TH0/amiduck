#include "ResultScene.h"
#include "../Engine/Image.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"
#include "../Engine/UI.h"
#include "../Observer/ResultObserver.h"

static SceneManager* pSceneManager;
static UI* pUI[(int)ResultScene::UIName::UI_MAX];

//コンストラクタ
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "TitleScne"), UIName_()
{
}

//初期化
void ResultScene::Initialize()
{
	std::string resultStr = "";

	//勝負によって変える
	if (ResultObserver::GetIsWin()) resultStr = "Clear\\win.png";
	else resultStr = "Clear\\lose.png";
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

	//UIの位置
	pUI[(int)UIName::FINISH]->SetPosition(0, -0.8, 0);
	pUI[(int)UIName::RETRY]->SetPosition(0, 0, 0);
	pUI[(int)UIName::BACK_TITLE]->SetPosition(0, -0.4f, 0);
	pUI[(int)UIName::RESULT]->SetPosition(0, 0.2f, 0);
}

//更新
void ResultScene::Update()
{
	if (Input::IsMouseButtonDown(0))
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
	switch (UIName_)
	{
	case ResultScene::UIName::UI_MAX:
		Image::SetColor(pUI[(int)UIName::RETRY]->GetHandle());
		Image::SetColor(pUI[(int)UIName::FINISH]->GetHandle());
		Image::SetColor(pUI[(int)UIName::BACK_TITLE]->GetHandle());
		break;
	case ResultScene::UIName::FINISH:
		Image::SetColor(pUI[(int)UIName::FINISH]->GetHandle(), 0.7f, 0.7f, 0.7f);
		Image::SetColor(pUI[(int)UIName::RETRY]->GetHandle());
		Image::SetColor(pUI[(int)UIName::BACK_TITLE]->GetHandle());
		break;
	case ResultScene::UIName::RETRY:
		Image::SetColor(pUI[(int)UIName::RETRY]->GetHandle(), 0.7f, 0.7f, 0.7f);
		Image::SetColor(pUI[(int)UIName::FINISH]->GetHandle());
		Image::SetColor(pUI[(int)UIName::BACK_TITLE]->GetHandle());
		break;
	case ResultScene::UIName::BACK_TITLE:
		Image::SetColor(pUI[(int)UIName::BACK_TITLE]->GetHandle(), 0.7f, 0.7f, 0.7f);
		Image::SetColor(pUI[(int)UIName::RETRY]->GetHandle());
		Image::SetColor(pUI[(int)UIName::FINISH]->GetHandle());
		break;
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
	for (int i = (int)ResultScene::UIName::FINISH; i < (int)ResultScene::UIName::UI_MAX; i++)
	{
		Image::Draw(pUI[i]->GetHandle());
	}
}

//開放
void ResultScene::Release()
{
}