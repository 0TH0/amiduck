#include "PlayScene.h"
#include "../Stage.h"
#include "../Instructions.h"
#include "../Controller.h"
#include "../FireFollowGround.h"
#include "../Line.h"
#include "../Water.h"
#include "../Item.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Text.h"
#include "../Engine/Audio.h"
#include "../Observer/ResultObserver.h"
#include "../EnemyRed.h"
#include "../EnemyBlue.h"
#include "../EnemyGreen.h"
#include "../Manager/PlaySceneGuide.h"

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

	//�����ɃZ�b�g
	ResultObserver::SetIsWin(false);

	//BGM
	hAudio_ = Audio::Load("Audio\\BGM.wav", 5);
	assert(hAudio_ >= 0);
}

//�X�V
void PlayScene::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");
	EnemyRed* pEnemyRed = (EnemyRed*)FindObject("EnemyRed");
	EnemyBlue* pEnemyBlue = (EnemyBlue*)FindObject("EnemyBlue");
	EnemyGreen* pEnemyGreen = (EnemyGreen*)FindObject("EnemyGreen");
	
	//����5��邩��莞�Ԃ��o�߂�����
	if (pEnemyRed == nullptr && pEnemyBlue == nullptr && pEnemyGreen == nullptr)
	{
		//�v���C���[�̏���
		ResultObserver::SetIsWin(true);
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