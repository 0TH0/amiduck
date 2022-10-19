#include "GameoverScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

//コンストラクタ
GameoverScene::GameoverScene(GameObject* parent)
	: GameObject(parent, "GameoverScene"), hPict_(-1)
{
}

//初期化
void GameoverScene::Initialize()
{
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
		pSceneManager->ChangeScene(SCENE_ID_START);
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

