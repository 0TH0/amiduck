#include "ClearScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "UI.h"

static SceneManager* pSceneManager;
static UI* pUI[(int)ClearScene::UIName::UI_MAX];

//コンストラクタ
ClearScene::ClearScene(GameObject* parent)
	: GameObject(parent, "TitleScne"), UIName_()
{
}

//初期化
void ClearScene::Initialize()
{
	std::string filename[] = {
		"Clear\\finish.png",
		"Clear\\retry.png",
		"Clear\\Clear.png",
		"Clear\\BackTitle.png",
	};

	float scale = 0.8f;
	for (int i = (int)ClearScene::UIName::FINISH; i < (int)ClearScene::UIName::UI_MAX; i++)
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
	pUI[(int)UIName::CLEAR]->SetPosition(0, 0.2f, 0);
}

//更新
void ClearScene::Update()
{
	if (Input::IsMouseButtonDown(0))
	{
		switch (UIName_)
		{
		case ClearScene::UIName::UI_MAX:
			break;
		case ClearScene::UIName::FINISH:
			PostQuitMessage(0);
			break;
		case ClearScene::UIName::RETRY:
			pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_PLAY);
			break;
		case ClearScene::UIName::BACK_TITLE:
			pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_TITLE);
			break;
		}
	}
	switch (UIName_)
	{
	case ClearScene::UIName::UI_MAX:
		Image::SetColor(pUI[(int)UIName::RETRY]->GetHandle());
		Image::SetColor(pUI[(int)UIName::FINISH]->GetHandle());
		Image::SetColor(pUI[(int)UIName::BACK_TITLE]->GetHandle());
		break;
	case ClearScene::UIName::FINISH:
		Image::SetColor(pUI[(int)UIName::FINISH]->GetHandle(), 0.7f, 0.7f, 0.7f);
		Image::SetColor(pUI[(int)UIName::RETRY]->GetHandle());
		Image::SetColor(pUI[(int)UIName::BACK_TITLE]->GetHandle());
		break;
	case ClearScene::UIName::RETRY:
		Image::SetColor(pUI[(int)UIName::RETRY]->GetHandle(), 0.7f, 0.7f, 0.7f);
		Image::SetColor(pUI[(int)UIName::FINISH]->GetHandle());
		Image::SetColor(pUI[(int)UIName::BACK_TITLE]->GetHandle());
		break;
	case ClearScene::UIName::BACK_TITLE:
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
void ClearScene::Draw()
{
	for (int i = (int)ClearScene::UIName::FINISH; i < (int)ClearScene::UIName::UI_MAX; i++)
	{
		Image::Draw(pUI[i]->GetHandle());
	}
}

//開放
void ClearScene::Release()
{
}