#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Sky.h"
#include "StartScene.h"
#include "GameoverScene.h"
#include "Instructions.h"
#include "Controller.h"
#include "FireFollowGround.h"

#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"
#include "Fire.h"

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

	pText = new Text;
	pText->Initialize();
}

//更新
void PlayScene::Update()
{

	Player* pPlayer = (Player*)FindObject("Player");

	FireFollowGround* pFireFollowGround;
	Fire* pFire;

	playerTrans.position_ = pPlayer->GetPosition();

	if (Input::IsKeyDown(DIK_3))
	{
		pFireFollowGround = Instantiate<FireFollowGround>(this);
		if (pPlayer->GetCoinCount() >= 3)
		{

			pPlayer->MinCoinCount(3);
		}
	}

	if (Input::IsKeyDown(DIK_4))
	{
		pFire = Instantiate<Fire>(this);
		if (pPlayer->GetCoinCount() >= 3)
		{

			pPlayer->MinCoinCount(3);
		}
	}

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

	if (FindObject("Enemy") == nullptr)
	{
		//プレイシーンに切り替え
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_CLEAR);
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