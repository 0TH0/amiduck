#include "StarUI.h"
#include "Engine/Image.h"
#include "Player.h"

#include "Engine/UI.h"

static Player* pPlayer;
static UI* pUI[5];
static int playerStarNum;
static int enemyStarNum;
static int starMax = 5;

//コンストラクタ
StarUI::StarUI(GameObject* parent)
	: GameObject(parent, "StarUI")
{
}

//初期化
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

//更新
void StarUI::Update()
{
	pPlayer = (Player*)FindObject("Player");
	playerStarNum = pPlayer->GetStarNum();

}

//描画
void StarUI::Draw()
{
	for (int i = 0; i < playerStarNum; i++)
	{
		Image::Draw(pUI[i]->GetHandle());
	}
}

//開放
void StarUI::Release()
{
}
