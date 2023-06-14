#include "TutorialScene.h"
#include "../Stage.h"
#include "../Player.h"
#include "../Enemy.h"
#include "../Instructions.h"
#include "../Controller.h"
#include "../FireFollowGround.h"
#include "../Fire.h"
#include "../Enemy.h"
#include "../Line.h"
#include "../Water.h"
#include "../Item.h"
#include "../Fire.h"
#include "../StarUI.h"
#include "../Duck.h"

#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Text.h"
#include "../Engine/Audio.h"
#include "../Observer/ResultObserver.h"

//コンストラクタ
TutorialScene::TutorialScene(GameObject* parent)
	: GameObject(parent, "TutorialScene"), hAudio_()
{
}

//初期化
void TutorialScene::Initialize()
{
	Instantiate<Water>(this);
	//ステージ
	Stage* pStage;
	pStage = Instantiate<Stage>(this);
	pStage->StageLoad();
	pStage->SetShouldPoPRandStage(true);

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
void TutorialScene::Update()
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
void TutorialScene::Draw()
{
}

//開放
void TutorialScene::Release()
{
}