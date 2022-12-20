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

#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//������
void PlayScene::Initialize()
{
	//�X�e�[�W
	Instantiate<Stage>(this);

	Stage* pStage = (Stage*)FindObject("Stage");
	Enemy* pEnemy = (Enemy*)FindObject("Enemy");

	//���f�����[�h
	pStage->StageLoad();
	pEnemy->EnemyLoad();

	Instantiate<Player>(this);
}

//�X�V
void PlayScene::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");

	FireFollowGround* pFireFollowGround;
	Fire* pFire;

	playerTrans.position_ = pPlayer->GetPosition();

	if (Input::IsKeyDown(DIK_3))
	{
		pFireFollowGround = Instantiate<FireFollowGround>(this);
		if (pPlayer->GetCoinCount() >= 3)
		{

			pPlayer->MinCoinCount(3);
		}
	}

	if (Input::IsKeyDown(DIK_4))
	{
		pFire = Instantiate<Fire>(this);
		if (pPlayer->GetCoinCount() >= 3)
		{

			pPlayer->MinCoinCount(3);
		}
	}

	//������@��\��
	if (Input::IsKey(DIK_M))
	{
		Instantiate<Instructions>(this);
	}

	if (FindObject("Player") == nullptr)
	{
		//�v���C�V�[���ɐ؂�ւ�
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_START);
	}

	if (FindObject("Enemy") == nullptr)
	{
		//�N���A�V�[���ɐ؂�ւ�
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_CLEAR);
	}

	if (Input::IsKey(DIK_E))
	{
		PostQuitMessage(0);	//�v���O�����I��
	}
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}