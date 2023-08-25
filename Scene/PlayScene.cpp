#include "PlayScene.h"
#include "../Stage/Stage.h"
#include "../Image/Instructions.h"
#include "../Player/Controller.h"
#include "../Stage/Water.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Text.h"
#include "../Engine/Audio.h"
#include "../Observer/ResultObserver.h"
#include "../Enemy/EnemyRed.h"
#include "../Enemy/EnemyBlue.h"
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
}

//�X�V
void PlayScene::Update()
{
	if (pTimer->GetRimit() <= 0)
	{
		//�v���C���[�̏���
		ResultObserver::SetIsWin(false);
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