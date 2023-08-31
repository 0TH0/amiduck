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

//�R���X�g���N�^
BombGuide::BombGuide(GameObject* parent)
	: GameObject(parent, "BombGuide"), hModel_(-1)
{
}

BombGuide::~BombGuide()
{
}

//������
void BombGuide::Initialize()
{
	//�����ʒu�̓v���C���[�̈ʒu�̂��{�P
	Player* pPlayer = (Player*)FindObject("Player");
	IsReturn_ = pPlayer->GetReturn();
	PlayerTrans_.position_ = pPlayer->GetPosition();
	transform_.position_ = PlayerTrans_.position_;
	transform_.position_.y = PlayerTrans_.position_.y + 1;
}

//�X�V
void BombGuide::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");
	pStage = (Stage*)FindObject("Stage");

	pStage->
}

//�`��
void BombGuide::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void BombGuide::Release()
{
}