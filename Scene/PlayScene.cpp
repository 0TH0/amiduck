#include "PlayScene.h"
#include "../Stage/Stage.h"
#include "../Image/Instructions.h"
#include "../Player/Controller.h"
#include "../Stage/Water.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Text.h"
#include "../Engine/Audio.h"
#include "../Observer/ResultObserver.h"
#include "../Enemy/EnemyRed.h"
#include "../Enemy/EnemyBlue.h"
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
}

//更新
void PlayScene::Update()
{
	if (pTimer->GetRimit() <= 0)
	{
		//プレイヤーの勝ち
		ResultObserver::SetIsWin(false);
		//リザルトシーンへ
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}
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