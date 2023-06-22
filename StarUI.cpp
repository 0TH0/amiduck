#include "StarUI.h"
#include "Engine/Image.h"
#include "Player.h"

#include "Engine/UI.h"

static Player* pPlayer;
static UI* pUI[5];
static int playerStarNum;
static int enemyStarNum;
static int starMax = 5;

//�R���X�g���N�^
StarUI::StarUI(GameObject* parent)
	: GameObject(parent, "StarUI")
{
}

//������
void StarUI::Initialize()
{
	for (int i = 0; i < starMax; i++)
	{
		pUI[i] = Instantiate<UI>(this);
		pUI[i]->Load("Image\\star_white.png");
		pUI[i]->SetScale(0.4f, 0.4f, 0.4f);
		Image::SetColor(pUI[i]->GetHandle(), 1, 1, 0);
		pUI[i]->SetPosition(-0.9f + (i * 0.1f), 0.85f, 0);
	}
}

//�X�V
void StarUI::Update()
{
	pPlayer = (Player*)FindObject("Player");
	playerStarNum = pPlayer->GetStarNum();

}

//�`��
void StarUI::Draw()
{
	for (int i = 0; i < playerStarNum; i++)
	{
		Image::Draw(pUI[i]->GetHandle());
	}
}

//�J��
void StarUI::Release()
{
}
