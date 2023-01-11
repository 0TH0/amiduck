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
#include "Fire.h"
#include "Enemy.h"
#include "Line.h"
#include "StartScene.h"

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
	Stage* pStage1;
	Stage* pStage2;
	//Instantiate<Stage>(this);
	pStage2 = Instantiate<Stage>(this);
	pStage2->SetPosition(XMFLOAT3(0, 0, 0));

	Stage* pStage = (Stage*)FindObject("Stage");
	Enemy* pEnemy = (Enemy*)FindObject("Enemy");

	//モデルロード
	//pStage->StageLoad();
	//pEnemy->EnemyLoad();

	Instantiate<Player>(this);
	Instantiate<StartScene>(this);
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
	}

	if (Input::IsKeyDown(DIK_4))
	{
		pFire = Instantiate<Fire>(this);
	}

	//操作方法を表示
	if (Input::IsKey(DIK_M))
	{
		Instantiate<Instructions>(this);
	}

	//if (FindObject("Enemy") == nullptr)
	//{
	//	//クリアシーンに切り替え
	//	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	//	pSceneManager->ChangeScene(SCENE_ID_CLEAR);
	//}
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}