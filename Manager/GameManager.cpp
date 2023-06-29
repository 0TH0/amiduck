#include "GameManager.h"
#include "../Star.h"
#include "../Engine/Input.h"
#include "../Player.h"
#include "../Observer/ResultObserver.h"
#include "../Engine/SceneManager.h"
#include "../EnemyRed.h"
#include "../EnemyBlue.h"
#include "../EnemyGreen.h"
#include "../Stage.h"

namespace
{
	Player* pPlayer;
	Star* pStar;
	EnemyRed* pEnemyRed;
	EnemyBlue* pEnemyBlue;
	EnemyGreen* pEnemyGreen;
	SceneManager* pSceneManager;
	Stage* pStage;
	const XMINT3 randPosMax_ = { 2, 0, 7 };
}

//コンストラクタ
GameManager::GameManager(GameObject * parent)
	: GameObject(parent, "GameManager"),randPos_(), timeMax_(300)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		EnemyTime_[i] = 0;
	}
}

//初期化
void GameManager::Initialize()
{
	//負けにセット
	ResultObserver::SetIsWin(false);

	pStage = (Stage*)FindObject("Stage");
	RandObject();
	pStar = Instantiate<Star>(this);
	pStar->SetPosition(randPos_.x, 3, randPos_.z);
}

//更新
void GameManager::Update()
{
	pPlayer = (Player*)FindObject("Player");
	pStage = (Stage*)FindObject("Stage");
	pEnemyRed = (EnemyRed*)FindObject("EnemyRed");
	pEnemyBlue = (EnemyBlue*)FindObject("EnemyBlue");
	pEnemyGreen = (EnemyGreen*)FindObject("EnemyGreen");

	if (pPlayer->GetStarNum() >= 5)
	{
		//プレイヤーの勝ち
		ResultObserver::SetIsWin(true);
		//リザルトシーンへ
		pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}
	else
	{
		PopStar();
	}

	EnemyReturn();
}

//描画
void GameManager::Draw()
{
}

//開放
void GameManager::Release()
{
}

void GameManager::PopStar()
{
	if (pPlayer->GetStarAfterTime() >= 120)
	{
		RandObject();
		pStar = Instantiate<Star>(this);
		pStar->SetPosition(randPos_.x, 3, randPos_.z);
		pPlayer->SetIsStar(false);
	}
}

//ランダムで星の位置を決める
void GameManager::RandObject()
{
	randPos_ = { rand() % randPosMax_.x, 0, rand() % randPosMax_.z };

	switch (randPos_.x)
	{
	case 0:
		randPos_.x = pStage->GetBridgeRimit();
		break;
	case 1:
		randPos_.x = pStage->GetStageSizeX() - pStage->GetBridgeRimit();
		break;
	default:
		break;
	}

	randPos_.z *= (randPosMax_.z - 1);
}

void GameManager::EnemyReturn()
{
	if (pEnemyRed == nullptr)
	{
		EnemyTime_[RED]++;
		if (EnemyTime_[RED] >= timeMax_)
		{
			RandObject();
			pEnemyRed = Instantiate<EnemyRed>(this);
			pEnemyRed->SetPosition(randPos_.x, 1.5f, randPos_.z);
			EnemyTime_[RED] = 0;
		}
	}
	if (pEnemyBlue == nullptr)
	{
		EnemyTime_[BLUE]++;
		if (EnemyTime_[BLUE] >= timeMax_)
		{
			RandObject();
			pEnemyBlue = Instantiate<EnemyBlue>(this);
			pEnemyBlue->SetPosition(randPos_.x, 1.5f, randPos_.z);
			EnemyTime_[BLUE] = 0;
		}
	}
	if (pEnemyGreen == nullptr)
	{
		EnemyTime_[GREEN]++;
		if (EnemyTime_[GREEN] >= timeMax_)
		{
			RandObject();
			pEnemyGreen = Instantiate<EnemyGreen>(this);
			pEnemyGreen->SetPosition(randPos_.x, 1.5f, randPos_.z);
			EnemyTime_[GREEN] = 0;
		}
	}
}