#include "TutorialScene.h"
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
#include "Pose.h"
#include "Timer.h"

static Timer* pTimer;

//�R���X�g���N�^
TutorialScene::TutorialScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//������
void TutorialScene::Initialize()
{
	Instantiate<Water>(this);
	//�X�e�[�W
	Stage* pStage;
	pStage = Instantiate<Stage>(this);
	pStage->SetShouldPoPRandStage(false);
	
	//Instantiate<StartScene>(this);
	//Instantiate<Pose>(this);

	////�^�C�}�[�\��
	//pTimer = Instantiate<Timer>(this);
	//pTimer->SetRimit(5);
	//pTimer->SetPosition(700, 0, 100);

	//Instantiate<Duck>(this);
	//Instantiate<StarUI>(this);
	//Instantiate<Instructions>(this);

	//pStage = (Stage*)FindObject("Stage");
	//Enemy* pEnemy = (Enemy*)FindObject("Enemy");

	////BGM
	//hAudio_ = Audio::Load("Audio\\BGM.wav", 5);
	//assert(hAudio_ >= 0);
}

//�X�V
void TutorialScene::Update()
{
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