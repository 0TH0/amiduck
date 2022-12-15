#include "StartScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/GameObject.h"
#include "PlayScene.h"
#include "Player.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"

//コンストラクタ
StartScene::StartScene(GameObject* parent)
	: GameObject(parent, "StartScene"), time(0), stock(3)
{
}

//初期化
void StartScene::Initialize()
{
	Camera::SetDefault();

	hPict_[0] = Image::Load("a.png");
	assert(hPict_[0] >= 0);

	pText = new Text;
	pText->Initialize();
}

//更新
void StartScene::Update()
{
	/*
	//時間
	time += 0.01f;

	if (time > 1.0f)
	{
		time = 0;
		KillMe();
	}
	*/
	Sleep(1*1000);

	if (FindObject("Player") == nullptr)
	{
		//プレイシーンに切り替え
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

//描画
void StartScene::Draw()
{
	Image::SetTransform(hPict_[0], transform_);
	Image::Draw(hPict_[0]);
	pText->Draw(775, 440, stock);
}

//開放
void StartScene::Release()
{
}