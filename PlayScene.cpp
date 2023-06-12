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

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),hAudio_(),pPlayer_()
{
}

//������
void PlayScene::Initialize()
{
	Instantiate<Water>(this);
	//�X�e�[�W
	Stage* pStage;
	pStage = Instantiate<Stage>(this);
	pStage->StageLoad();
	pStage->SetShouldPoPRandStage(true);

	Instantiate<StartScene>(this);
	
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
void PlayScene::Update()
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
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}