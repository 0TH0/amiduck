#include "StarUI.h"
#include "../Engine/Image.h"
#include "../Player.h"
#include "../Engine/UI.h"

namespace
{
	static Player* pPlayer;		//�v���C���[
	static UI* pUI[5];			//���T��
	static int playerStarNum;	//�v���C���[�̐��̐�������
	static int MAX_STAR = 5;	//�ő�̐��̐�
	static float starScale = 0.4f;
	static XMFLOAT3 starPos = { -0.9f, 0.1f, 0.85f };
}

//�R���X�g���N�^
StarUI::StarUI(GameObject* parent)
	: GameObject(parent, "StarUI")
{
}

//������
void StarUI::Initialize()
{
	for (int i = 0; i < MAX_STAR; i++)
	{
		pUI[i] = Instantiate<UI>(this);
		pUI[i]->Load("Image\\star_white.png");
		pUI[i]->SetScale(starScale, starScale, starScale);
		//�ŏ��͍�
		Image::SetColor(pUI[i]->GetHandle(), 0, 0, 0);
		pUI[i]->SetPosition(starPos.x + (i * starPos.y), starPos.z, 0);
	}
}

//�X�V
void StarUI::Update()
{
	pPlayer = (Player*)FindObject("Player");
	playerStarNum = pPlayer->GetStarNum();

	//���̐������F�ɂ���
	for (int i = 0; i < playerStarNum; i++)
	{
		Image::SetColor(pUI[i]->GetHandle(), 1, 1, 0);
	}
}

//�`��
void StarUI::Draw()
{
	for (int i = 0; i < MAX_STAR; i++)
	{
		Image::Draw(pUI[i]->GetHandle());
	}
}

//�J��
void StarUI::Release()
{
}