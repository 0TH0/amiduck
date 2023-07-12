#include "sceneManager.h"
#include "../Scene/PlayScene.h"
#include "../Scene/TitleScene.h"
#include "../Scene/ResultScene.h"
#include "Model.h"
#include "Image.h"
#include "Audio.h"
#include "Input.h"
#include "VFX.h"

//�R���X�g���N�^
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager")
{
}

//������
void SceneManager::Initialize()
{
	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID_RESULT;
	nextSceneID_ = currentSceneID_;
	Instantiate<ResultScene>(this);
}

//�X�V
void SceneManager::Update()
{
	//���̃V�[�������݂̃V�[���ƈႤ�@���@�V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
	if (currentSceneID_ != nextSceneID_)
	{
		//���[�h�����f�[�^��S�폜
		//Audio::Release();
		Model::AllRelease();
		Image::AllRelease();
		VFX::Release();

		//���̃V�[���̃I�u�W�F�N�g��S�폜
		KillAllChildren();
		
		//���̃V�[�����쐬
		switch (nextSceneID_)
		{
		case SCENE_ID_TITLE: Instantiate<TitleScene>(this); break;
		case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;
		case SCENE_ID_RESULT: Instantiate<ResultScene>(this); break;
		}
		Audio::Initialize();
		currentSceneID_ = nextSceneID_;
	}
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