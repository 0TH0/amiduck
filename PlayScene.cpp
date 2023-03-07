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
#include "Mushroom.h"

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
	Stage* pStage;
	pStage = Instantiate<Stage>(this);
	pStage->StageLoad();;

	Instantiate<Mushroom>(this);
	Instantiate<StartScene>(this);
	
	pStage = (Stage*)FindObject("Stage");
	Enemy* pEnemy = (Enemy*)FindObject("Enemy");

	//BGM
	hAudio_ = Audio::Load("Audio\\BGM.wav", 5);
	assert(hAudio_ >= 0);
}

//更新
void PlayScene::Update()
{
	//Player* pPlayer_ = (Player*)FindObject("Player");

	//playerTrans.position_ = pPlayer_->GetPosition();

	//操作方法を表示
	//if (Input::IsKey(DIK_M))
	//{
	//	Instantiate<Instructions>(this);
	//}

	//BGM再生
	//Audio::Play(hAudio_);
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}