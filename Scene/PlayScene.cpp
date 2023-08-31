#include "PlayScene.h"
#include "../Stage/Stage.h"
#include "../Image/Instructions.h"
#include "../Player/Controller.h"
#include "../Stage/Water.h"
#include "../Item/Star.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Audio.h"
#include "../Observer/ResultObserver.h"
#include "../Enemy/EnemyWhite.h"
#include "../Enemy/EnemyYellow.h"
#include "../Enemy/EnemyGreen.h"
#include "../Manager/PlaySceneGuide.h"
#include "../Item/StarUI.h"
#include "../Manager/GameManager.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),hAudio_(),pTimer()
{
}

//������
void PlayScene::Initialize()
{
	Instantiate<Water>(this);
	//�X�e�[�W
	Stage* pStage;
	pStage = Instantiate<Stage>(this);
	
	//�^�C�}�[�\��
	pTimer = Instantiate<Timer>(this);
	pTimer->SetRimit(180);
	pTimer->SetPosition(700, 0, 100);

	//�������
	Instantiate<Instructions>(this);

	//��������
	Instantiate<PlaySceneGuide>(this);

	//����UI
	Instantiate<StarUI>(this);

	//�Q�[���̐i�s�Ǘ�
	Instantiate<GameManager>(this);

	//BGM
	hAudio_ = Audio::Load("Audio\\BGM.wav");
	assert(hAudio_ >= 0);

	//BGM�Đ�
	Audio::PlayLoop(hAudio_);
}

//�X�V
void PlayScene::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");

	//�������Ԃ��O���Q�[���I�[�o�[
	if (pTimer->GetRimit() <= 0 || pPlayer->GetIsGameOver())
	{
		//�v���C���[�̕���
		ResultObserver::SetIsWin(false);
		Audio::Stop(hAudio_);

		//���U���g�V�[����
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}
	if (pPlayer->GetStarNum() >= MAX_STAR)
	{
		//�v���C���[�̏���
		ResultObserver::SetIsWin(true);
		Audio::Stop(hAudio_);
		//���U���g�V�[����
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
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