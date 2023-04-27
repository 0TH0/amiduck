#include "StarUI.h"
#include "Engine/Image.h"
#include "Player.h"
#include "Enemy.h"

Player* pPlayer;
Enemy* pEnemy;
static int hPict;
static int playerStarNum;
static int enemyStarNum;

//�R���X�g���N�^
StarUI::StarUI(GameObject* parent)
	: GameObject(parent, "TestScene")
{
}

//������
void StarUI::Initialize()
{
	hPict = Image::Load("Image\\star_white.png");
	assert(hPict >= 0);
}

//�X�V
void StarUI::Update()
{
	pPlayer = (Player*)FindObject("Player");
	playerStarNum = pPlayer->GetStarNum();

	pEnemy = (Enemy*)FindObject("Enemy");
	//enemyStarNum = pEnemy->getsta;
}

//�`��
void StarUI::Draw()
{
	for (int i = 0; i < playerStarNum; i++)
	{
		transform_.position_ = XMFLOAT3(-0.6f + (i * 0.15f), 0.85f ,0);
		transform_.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5f);
		Image::SetColor(hPict, 1, 1, 0);
		Image::SetTransform(hPict, transform_);
		Image::Draw(hPict);
	}
}

//�J��
void StarUI::Release()
{
}
