#include "TutorialScece.h"
#include "../Engine/Image.h"
#include "../Engine/UI.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"

namespace
{
	static UI* pPlayBt;
	XMFLOAT3 PosPlayBt;
	SceneManager* pSceneManager;
	static const int MAX_TIME = 120;
}

//�R���X�g���N�^
TutorialScece::TutorialScece(GameObject* parent)
	: GameObject(parent, "TutorialScece"), hPict_(-1)
{
}

//������
void TutorialScece::Initialize()
{
	hPict_ = Image::Load("Image\\tutorial.jpg");
	assert(hPict_ >= 0);

	pPlayBt = Instantiate<UI>(this);
	pPlayBt->Load("Image\\playBt.png");
	PosPlayBt.y = -0.6f;
	assert(pPlayBt->GetHandle() >= 0);
}

//�X�V
void TutorialScece::Update()
{
	time_++;

	//�Q�b�o������
	if (time_ >= MAX_TIME)
	{
		pPlayBt->SetShouldUseHitCursor(true);

		//�J�[�\���摜�̈ʒu�ō��N���b�N������
		if (Image::IsHitCursor(pPlayBt->GetHandle()) && Input::IsMouseButtonDown(Input::LEFT))
		{
			pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_PLAY);
		}
	}
}

//�`��
void TutorialScece::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	pPlayBt->SetUIPosition(PosPlayBt);
	Image::Draw(pPlayBt->GetHandle());
}

//�J��
void TutorialScece::Release()
{
}
