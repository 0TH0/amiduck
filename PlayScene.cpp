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
	//�X�e�[�W
	Instantiate<Stage>(this);
	Stage* pStage = (Stage*)FindObject("Stage");
	//�X�e�[�W�̃��f�����[�h
	pStage->StageLoad();

	Instantiate<Player>(this);
	Instantiate<Enemy>(this);

	Instructions pInstructions = (Instructions*)FindObject("Instructions");

	pText = new Text;
	pText->Initialize();
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