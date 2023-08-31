#include "BombGuide.h"
#include "../Engine/Model.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"
#include "../Player/Player.h"
#include "../Manager/EffectManager.h"
#include "../Manager/AudioManager.h"

namespace
{
	static const int MAX_TIME = 100;
	static const int MAX_STAR_DELAY = 7;
}

//コンストラクタ
BombGuide::BombGuide(GameObject* parent)
	: GameObject(parent, "BombGuide"), hModel_(-1)
{
}

BombGuide::~BombGuide()
{
}

//初期化
void BombGuide::Initialize()
{
	//初期位置はプレイヤーの位置のｙ＋１
	Player* pPlayer = (Player*)FindObject("Player");
	IsReturn_ = pPlayer->GetReturn();
	PlayerTrans_.position_ = pPlayer->GetPosition();
	transform_.position_ = PlayerTrans_.position_;
	transform_.position_.y = PlayerTrans_.position_.y + 1;
}

//更新
void BombGuide::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");
	pStage = (Stage*)FindObject("Stage");

	pStage->
}

//描画
void BombGuide::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void BombGuide::Release()
{
}