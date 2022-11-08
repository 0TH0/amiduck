#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Sky.h"
#include "StartScene.h"
#include "GameoverScene.h"
#include "Instructions.h"

#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	//ステージ
	Instantiate<Stage>(this);
	Stage* pStage = (Stage*)FindObject("Stage");
	//ステージのモデルロード
	pStage->StageLoad();

	Instantiate<Player>(this);
	Instantiate<Enemy>(this);

	Instructions pInstructions = (Instructions*)FindObject("Instructions");

	pText = new Text;
	pText->Initialize();
}

//更新
void PlayScene::Update()
{
	//操作方法を表示
	if (Input::IsKey(DIK_M))
	{
		Instantiate<Instructions>(this);
	}

	if (FindObject("Player") == nullptr)
	{
		//プレイシーンに切り替え
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_START);
	}
	if (Input::IsKey(DIK_E))
	{
		PostQuitMessage(0);	//プログラム終了
	}
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}