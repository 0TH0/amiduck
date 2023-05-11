#include "sceneManager.h"
#include "../ClearScene.h"
#include "../StartScene.h"
#include "../GameoverScene.h"
#include "../PlayScene.h"
#include "../TitleScene.h"
#include "Model.h"
#include "Image.h"
#include "Audio.h"
#include "Input.h"


//�R���X�g���N�^
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager")
{
}

//������
void SceneManager::Initialize()
{
	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);
}

//�X�V
void SceneManager::Update()
{
	//���̃V�[�������݂̃V�[���ƈႤ�@���@�V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
	if (currentSceneID_ != nextSceneID_)
	{
		//���̃V�[���̃I�u�W�F�N�g��S�폜
		KillAllChildren();

		//���[�h�����f�[�^��S�폜
		//Audio::Release();
		Model::AllRelease();
		Image::AllRelease();

		//���̃V�[�����쐬
		switch (nextSceneID_)
		{
		case SCENE_ID_START: Instantiate<StartScene>(this); break;
		case SCENE_ID_TITLE: Instantiate<TitleScene>(this); break;
		case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;
		case SCENE_ID_CLEAR: Instantiate<ClearScene>(this); break;
		case SCENE_ID_GAMEOVER: Instantiate<GameOverScene>(this); break;
		case SCENE_ID_TUTORIAL: break;
		}
		Audio::Initialize();
		currentSceneID_ = nextSceneID_;
	}

	//if (Input::IsKey(DIK_E))
	//{
	//	PostQuitMessage(0);	//�v���O�����I��
	//}
}

//�`��
void SceneManager::Draw()
{
}

//�J��
void SceneManager::Release()
{
}

//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;
}