#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Sky.h"
#include "StartScene.h"
#include "GameoverScene.h"
#include "Instructions.h"

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
	//Instantiate<Sky>(this);
	Instantiate<Stage>(this);
	Instantiate<Player>(this);

	Instructions pInstructions = (Instructions*)FindObject("Instructions");

	pText = new Text;
	pText->Initialize();

	Stage* pStage = (Stage*)FindObject("Stage");
	pStage->StageLoad();
}

//�X�V
void PlayScene::Update()
{
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