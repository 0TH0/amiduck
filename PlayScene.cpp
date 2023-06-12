#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "StartScene.h"
#include "Instructions.h"
#include "Controller.h"
#include "FireFollowGround.h"
#include "Fire.h"
#include "Enemy.h"
#include "Line.h"
#include "StartScene.h"
#include "Water.h"
#include "Item.h"
#include "Fire.h"
#include "StarUI.h"
#include "Duck.h"

#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"
#include "Engine/Audio.h"
#include "Timer.h"
#include "Observer/ResultObserver.h"

static Timer* pTimer;

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),hAudio_(),pPlayer_()
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Water>(this);
	//ステージ
	Stage* pStage;
	pStage = Instantiate<Stage>(this);
	pStage->StageLoad();
	pStage->SetShouldPoPRandStage(true);

	Instantiate<StartScene>(this);
	
	//タイマー表示
	pTimer = Instantiate<Timer>(this);
	pTimer->SetRimit(180);
	pTimer->SetPosition(700, 0, 100);

	Instantiate<Duck>(this);
	Instantiate<StarUI>(this);
	Instantiate<Instructions>(this);

	//BGM
	hAudio_ = Audio::Load("Audio\\BGM.wav", 5);
	assert(hAudio_ >= 0);
}

//更新
void PlayScene::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");

	//星を5個取るか一定時間が経過したら
	if (pPlayer->GetStarNum() >= 5 || pTimer->GetRimit() <= 0)
	{
		Enemy* pEnemy = (Enemy*)FindObject("Enemy");

		//敵の星の数の方が多かったら
		if (pEnemy->GetStarNum() >= pPlayer->GetStarNum())
		{
			//プレイヤーの負け
			ResultObserver::SetIsWin(false);
		}
		else
		{
			//プレイヤーの勝ち
			ResultObserver::SetIsWin(true);
		}
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