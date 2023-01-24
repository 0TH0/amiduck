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
#include "Water.h"
#include "ItemUI.h"
#include "Coin.h"

#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"
#include "Engine/Audio.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Water>(this);
	//ステージ
	Stage* pStage = Instantiate<Stage>(this);
	
	pStage = (Stage*)FindObject("Stage");
	Enemy* pEnemy = (Enemy*)FindObject("Enemy");

	Instantiate<StartScene>(this);
	Instantiate<ItemUI>(this);

	//空中コイン仮
	for (int i = 0; i < 100; i++)
	{
		Coin* pCoin = Instantiate<Coin>(this);
		pCoin->SetPosition(20 + i, 10 + i, 20);
	}

	//BGM
	hAudio_ = Audio::Load("Audio\\BGM.wav", 5);
	assert(hAudio_ >= 0);
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

	//BGM再生
	Audio::Play(hAudio_);
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}