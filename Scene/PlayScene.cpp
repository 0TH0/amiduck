#include "PlayScene.h"
#include "../Stage.h"
#include "../Instructions.h"
#include "../Controller.h"
#include "../FireFollowGround.h"
#include "../Line.h"
#include "../Water.h"
#include "../Item.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Text.h"
#include "../Engine/Audio.h"
#include "../Observer/ResultObserver.h"
#include "../EnemyRed.h"
#include "../EnemyBlue.h"
#include "../EnemyGreen.h"
#include "../Manager/PlaySceneGuide.h"

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

	//負けにセット
	ResultObserver::SetIsWin(false);

	//BGM
	hAudio_ = Audio::Load("Audio\\BGM.wav", 5);
	assert(hAudio_ >= 0);
}

//更新
void PlayScene::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");
	EnemyRed* pEnemyRed = (EnemyRed*)FindObject("EnemyRed");
	EnemyBlue* pEnemyBlue = (EnemyBlue*)FindObject("EnemyBlue");
	EnemyGreen* pEnemyGreen = (EnemyGreen*)FindObject("EnemyGreen");
	
	//星を5個取るか一定時間が経過したら
	if (pEnemyRed == nullptr && pEnemyBlue == nullptr && pEnemyGreen == nullptr)
	{
		//プレイヤーの勝ち
		ResultObserver::SetIsWin(true);
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