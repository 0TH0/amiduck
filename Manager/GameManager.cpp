#include "GameManager.h"
#include "../Item/Star.h"
#include "../Engine/Input.h"
#include "../Player/Player.h"
#include "../Observer/ResultObserver.h"
#include "../Engine/SceneManager.h"
#include "../Enemy/EnemyWhite.h"
#include "../Enemy/EnemyYellow.h"
#include "../Enemy/EnemyGreen.h"
#include "../Stage/Stage.h"
#include "../Item/Star.h"

namespace
{
	static Player* pPlayer;
	static Star* pStar;
	static EnemyWhite* pEnemyWhite;
	static EnemyYellow* pEnemyYellow;
	static EnemyGreen* pEnemyGreen;
	static SceneManager* pSceneManager;
	static Stage* pStage;
	static const XMINT3 MAX_RANDPOS = { 2, 0, 7 };
}

//コンストラクタ
GameManager::GameManager(GameObject* parent)
	: GameObject(parent, "GameManager"), MAX_TIME(300), randPos_({ 0,5,0 })
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
	
	pStar->SetPosition((float)randPos_.x, (float)randPos_.y, (float)randPos_.z);
}

//更新
void GameManager::Update()
{
	pPlayer = (Player*)FindObject("Player");
	pStage = (Stage*)FindObject("Stage");
	pEnemyWhite = (EnemyWhite*)FindObject("EnemyWhite");
	pEnemyYellow = (EnemyYellow*)FindObject("EnemyYellow");
	pEnemyGreen = (EnemyGreen*)FindObject("EnemyGreen");

	if (pPlayer->GetStarNum() < MAX_STAR)
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
	if (pPlayer->GetStarAfterTime() >= MAX_STAR_AFTER_TIME)
	{
		RandObject();
		pStar = Instantiate<Star>(this);
		pStar->SetPosition(randPos_.x, randPos_.y, randPos_.z);
		pPlayer->SetIsStar(false);
	}
}

//ランダムで星の位置を決める
void GameManager::RandObject()
{
	randPos_ = { rand() % MAX_RANDPOS.x, randPos_.y, rand() % MAX_RANDPOS.z };

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

	randPos_.z *= (MAX_RANDPOS.z - 1);
}

void GameManager::EnemyReturn()
{
	if (pEnemyWhite == nullptr)
	{
		EnemyTime_[RED]++;
		if (EnemyTime_[RED] >= MAX_TIME)
		{
			RandObject();
			pEnemyWhite = Instantiate<EnemyWhite>(this);
			pEnemyWhite->SetPosition(randPos_.x, randPos_.y, randPos_.z);
			EnemyTime_[RED] = 0;
		}
	}
	if (pEnemyYellow == nullptr)
	{
		EnemyTime_[BLUE]++;
		if (EnemyTime_[BLUE] >= MAX_TIME)
		{
			RandObject();
			pEnemyYellow = Instantiate<EnemyYellow>(this);
			pEnemyYellow->SetPosition(randPos_.x, randPos_.y, randPos_.z);
			EnemyTime_[BLUE] = 0;
		}
	}
	if (pEnemyGreen == nullptr)
	{
		EnemyTime_[GREEN]++;
		if (EnemyTime_[GREEN] >= MAX_TIME)
		{
			RandObject();
			pEnemyGreen = Instantiate<EnemyGreen>(this);
			pEnemyGreen->SetPosition(randPos_.x, randPos_.y, randPos_.z);
			EnemyTime_[GREEN] = 0;
		}
	}
}