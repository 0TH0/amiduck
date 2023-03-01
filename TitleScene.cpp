#include "TitleScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

SceneManager* pSceneManager;

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TitleScene::Initialize()
{
	hPict_ = Image::Load("Title\\TitleLogo.png");
	assert(hPict_ >= 0);

	hPictPlay_= Image::Load("Title\\playBt.png");
	assert(hPictPlay_ >= 0);

	hPictTuto_ = Image::Load("Title\\tutorialBt.png");
	assert(hPictTuto_ >= 0);

	hPictCh_ = Image::Load("Title\\title_ch.png");
	assert(hPictCh_ >= 0);
}

//更新
void TitleScene::Update()
{
	if (Input::IsMouseButtonDown(0))
	{
		switch (btState_)
		{
		case TitleScene::BtState::NONE:
			break;
		case TitleScene::BtState::PLAY:
			pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_PLAY);
			break;
		case TitleScene::BtState::Tutorial:
			pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_TUTORIAL);
			break;
		}
	}

	switch (btState_)
	{
	case TitleScene::BtState::NONE:
		Image::SetColor(hPictTuto_);
		Image::SetColor(hPictPlay_);
		break;
	case TitleScene::BtState::PLAY:
		Image::SetColor(hPictPlay_, 0.7f, 0.7f, 0.7f);
		Image::SetColor(hPictTuto_);
		break;
	case TitleScene::BtState::Tutorial:
		Image::SetColor(hPictTuto_, 0.7f, 0.7f, 0.7f);
		Image::SetColor(hPictPlay_);
		break;
	}

	//プレイ画面
	if (Image::IsHitCursor(hPictPlay_))
	{
		btState_ = BtState::PLAY;
	}
	else
	{
		if(btState_ == BtState::PLAY) btState_ = BtState::NONE;
	}

	//チュートリアル画面
	if (Image::IsHitCursor(hPictTuto_))
	{
		btState_ = BtState::Tutorial;
	}
	else
	{
		if (btState_ == BtState::Tutorial) btState_ = BtState::NONE;
	}
}

//描画
void TitleScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	Transform trans;
	trans.position_ = XMFLOAT3(0.4f, -0.6f, 0);
	trans.scale_ = XMFLOAT3(0.7, 0.7, 0.7);

	Image::SetTransform(hPictPlay_, trans);
	Image::Draw(hPictPlay_);

	Transform trans2;
	trans2.position_ = XMFLOAT3(-0.4f, -0.6f, 0);
	trans2.scale_ = XMFLOAT3(0.7, 0.7, 0.7);

	Image::SetTransform(hPictTuto_, trans2);
	Image::Draw(hPictTuto_);

	Transform trans3;
	trans3.position_ = XMFLOAT3(0, -0.2f, 0);

	Image::SetTransform(hPictCh_, trans3);
	Image::Draw(hPictCh_);
	Image::FlashImage(hPictCh_);
}

//開放
void TitleScene::Release()
{
}
