#include "ClearScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
ClearScene::ClearScene(GameObject* parent)
	: GameObject(parent, "ClearScene"), hPict_(-1)
{
}

//������
void ClearScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("Image\\CLEAR.png");
	assert(hPict_ >= 0);

	
	Camera::SetDefault();
}

//�X�V
void ClearScene::Update()
{
	if (Input::IsKey(DIK_RETURN))
	{
		//�v���C�V�[���ɐ؂�ւ�
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}

	if (Input::IsKey(DIK_E))
	{
		PostQuitMessage(0);	//�v���O�����I��
	}
}

//�`��
void ClearScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void ClearScene::Release()
{
}
