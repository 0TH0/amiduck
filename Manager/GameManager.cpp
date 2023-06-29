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

//�R���X�g���N�^
GameManager::GameManager(GameObject * parent)
	: GameObject(parent, "GameManager"),randPos_()
{
}

//������
void GameManager::Initialize()
{
	//�����ɃZ�b�g
	ResultObserver::SetIsWin(false);

	pStage = (Stage*)FindObject("Stage");
	RandStar();
	pStar = Instantiate<Star>(this);
	pStar->SetPosition(randPos_.x, 3, randPos_.z);
}

//�X�V
void GameManager::Update()
{
	pPlayer = (Player*)FindObject("Player");
	pStage = (Stage*)FindObject("Stage");
	pEnemyRed = (EnemyRed*)FindObject("EnemyRed");
	pEnemyBlue = (EnemyBlue*)FindObject("EnemyBlue");
	pEnemyGreen = (EnemyGreen*)FindObject("EnemyGreen");

	switch (pPlayer->GetStarNum())
	{
	case 1:
	case 2:
	case 3:
	case 4:
		PopStar();
		break;
	case 5:
		//�v���C���[�̏���
		ResultObserver::SetIsWin(true);
		//���U���g�V�[����
		pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
		break;
	default:
		break;
	}
}

//�`��
void GameManager::Draw()
{
}

//�J��
void GameManager::Release()
{
}

void GameManager::PopStar()
{
	if (pPlayer->GetStarAfterTime() >= 120)
	{
		RandStar();
		pStar = Instantiate<Star>(this);
		pStar->SetPosition(randPos_.x, 3, randPos_.z);
		pPlayer->SetIsStar(false);
	}
}

//�����_���Ő��̈ʒu�����߂�
void GameManager::RandStar()
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