#include "GameoverScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"


//コンストラクタ
GameoverScene::GameoverScene(GameObject* parent)
	: GameObject(parent, "GameoverScene"), hPict_(-1)
{
}

//初期化
void GameoverScene::Initialize()
{
	//全画面表示する
	Direct3D::SetViewPort(Direct3D::SCREEN_DEFAULT);
	Camera::SetDefault();

	//画像データのロード
	hPict_ = Image::Load("GameOver.png");
	assert(hPict_ >= 0);
}

//更新
void GameoverScene::Update()
{
	if (Input::IsKey(DIK_RETURN))
	{
		//プレイシーンに切り替え
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

//描画
void GameoverScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void GameoverScene::Release()
{
}

