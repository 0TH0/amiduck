#include "PlayScene.h"
#include "../Stage/Stage.h"
#include "../Image/Instructions.h"
#include "../Player/Controller.h"
#include "../Stage/Water.h"
#include "../Item/Star.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Audio.h"
#include "../Observer/ResultObserver.h"
#include "../Enemy/EnemyWhite.h"
#include "../Enemy/EnemyYellow.h"
#include "../Enemy/EnemyGreen.h"
#include "../Manager/PlaySceneGuide.h"
#include "../Item/StarUI.h"
#include "../Manager/GameManager.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),hAudio_(),pTimer()
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Water>(this);
	//ステージ
	Stage* pStage;
	pStage = Instantiate<Stage>(this);
	
	//タイマー表示
	pTimer = Instantiate<Timer>(this);
	pTimer->SetRimit(180);
	pTimer->SetPosition(700, 0, 100);

	//操作説明
	Instantiate<Instructions>(this);

	//勝利条件
	Instantiate<PlaySceneGuide>(this);

	//星のUI
	Instantiate<StarUI>(this);

	//ゲームの進行管理
	Instantiate<GameManager>(this);

	//BGM
	hAudio_ = Audio::Load("Audio\\BGM.wav");
	assert(hAudio_ >= 0);

	//BGM再生
	Audio::PlayLoop(hAudio_);
}

//更新
void PlayScene::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");

	//制限時間が０かゲームオーバー
	if (pTimer->GetRimit() <= 0 || pPlayer->GetIsGameOver())
	{
		//プレイヤーの負け
		ResultObserver::SetIsWin(false);
		Audio::Stop(hAudio_);

		//リザルトシーンへ
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}
	if (pPlayer->GetStarNum() >= MAX_STAR)
	{
		//プレイヤーの勝ち
		ResultObserver::SetIsWin(true);
		Audio::Stop(hAudio_);
		//リザルトシーンへ
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
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