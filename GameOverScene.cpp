#include "GameoverScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

//�R���X�g���N�^
GameoverScene::GameoverScene(GameObject* parent)
	: GameObject(parent, "GameoverScene"), hPict_(-1)
{
}

//������
void GameoverScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("GameOver.png");
	assert(hPict_ >= 0);
}

//�X�V
void GameoverScene::Update()
{
	if (Input::IsKey(DIK_RETURN))
	{
		//�v���C�V�[���ɐ؂�ւ�
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_START);
	}
}

//�`��
void GameoverScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void GameoverScene::Release()
{
}

