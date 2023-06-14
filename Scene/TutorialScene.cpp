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

//�R���X�g���N�^
TutorialScene::TutorialScene(GameObject* parent)
	: GameObject(parent, "TutorialScene"), hAudio_()
{
}

//������
void TutorialScene::Initialize()
{
	Instantiate<Water>(this);
	//�X�e�[�W
	Stage* pStage;
	pStage = Instantiate<Stage>(this);
	pStage->StageLoad();
	pStage->SetShouldPoPRandStage(true);

	//�^�C�}�[�\��
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

//�X�V
void TutorialScene::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");

	//����5��邩��莞�Ԃ��o�߂�����
	if (pPlayer->GetStarNum() >= 5 || pTimer->GetRimit() <= 0)
	{
		Enemy* pEnemy = (Enemy*)FindObject("Enemy");

		//�G�̐��̐��̕�������������
		if (pEnemy->GetStarNum() >= pPlayer->GetStarNum())
		{
			//�v���C���[�̕���
			ResultObserver::SetIsWin(false);
		}
		else
		{
			//�v���C���[�̏���
			ResultObserver::SetIsWin(true);
		}
		//���U���g�V�[����
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}

	//BGM�Đ�
	Audio::Play(hAudio_);
}

//�`��
void TutorialScene::Draw()
{
}

//�J��
void TutorialScene::Release()
{
}