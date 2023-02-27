#include "TitleScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

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

	hPictCh_ = Image::Load("Title\\start.png");
	assert(hPictCh_ >= 0);
}

//更新
void TitleScene::Update()
{
	//何かキーが押されたら
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}

	if (Image::IsHitCursor(hPictCh_))
	{
		Image::SetColor(hPictCh_, 0.7f, 0.7f, 0.7f);
		if (Input::IsMouseButtonDown(0))
		{
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_PLAY);
		}
	}
	else
	{
		Image::SetColor(hPictCh_, 1.f, 1.f, 1.f);
	}
}

//描画
void TitleScene::Draw()
{
	transform_.position_.y = 0.25f;
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	Transform trans;
	trans.position_.y = -0.6;
	trans.scale_ = XMFLOAT3(0.7, 0.7, 0.7);

	Image::SetTransform(hPictCh_, trans);
	Image::Draw(hPictCh_);
	/*Image::FlashImage(hPictCh_, 5);*/
}

//開放
void TitleScene::Release()
{
}
