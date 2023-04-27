#include "StarUI.h"
#include "Engine/Image.h"
#include "Player.h"
#include "Enemy.h"

Player* pPlayer;
Enemy* pEnemy;
static int hPict;
static int playerStarNum;
static int enemyStarNum;

//コンストラクタ
StarUI::StarUI(GameObject* parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void StarUI::Initialize()
{
	hPict = Image::Load("Image\\star_white.png");
	assert(hPict >= 0);
}

//更新
void StarUI::Update()
{
	pPlayer = (Player*)FindObject("Player");
	playerStarNum = pPlayer->GetStarNum();

	pEnemy = (Enemy*)FindObject("Enemy");
	//enemyStarNum = pEnemy->getsta;
}

//描画
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

//開放
void StarUI::Release()
{
}
