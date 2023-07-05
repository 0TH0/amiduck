#include "StarUI.h"
#include "Engine/Image.h"
#include "Player.h"
#include "Engine/UI.h"

namespace
{
	static Player* pPlayer;		//プレイヤー
	static UI* pUI[5];			//星５つ分
	static int playerStarNum;	//プレイヤーの星の数を入れる
	static int MAX_STAR = 5;	//最大の星の数
	static float starScale = 0.4f;
	static XMFLOAT3 starPos = { -0.9f, 0.1f, 0.85f };
}

//コンストラクタ
StarUI::StarUI(GameObject* parent)
	: GameObject(parent, "StarUI")
{
}

//初期化
void StarUI::Initialize()
{
	for (int i = 0; i < MAX_STAR; i++)
	{
		pUI[i] = Instantiate<UI>(this);
		pUI[i]->Load("Image\\star_white.png");
		pUI[i]->SetScale(starScale, starScale, starScale);
		Image::SetColor(pUI[i]->GetHandle(), 1, 1, 0);
		pUI[i]->SetPosition(starPos.x + (i * starPos.y), starPos.z, 0);
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