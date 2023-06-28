#include "Bomb.h"
#include "Engine/Model.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Player.h"
#include "Manager/BombEffect.h"

//�R���X�g���N�^
Bomb::Bomb(GameObject* parent)
	: GameObject(parent, "Bomb"), hModel_(-1)
{
}

Bomb::~Bomb()
{
}

//������
void Bomb::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hModel_ = Model::Load("Model\\bomb.fbx");
	assert(hModel_ >= 0);

	//�����蔻��
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.5f);
	AddCollider(collision);

	transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35);

	transform_.rotate_ = XMFLOAT3(0, 0, 0);

	//�����ʒu�̓v���C���[�̈ʒu�̂��{�P
	Player* pPlayer = (Player*)FindObject("Player");
	IsReturn_ = pPlayer->GetReturn();
	PlayerTrans_.position_ = pPlayer->GetPosition();
	transform_.position_ = PlayerTrans_.position_;
	transform_.position_.y = PlayerTrans_.position_.y + 1;
}

//�X�V
void Bomb::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");
	transform_.rotate_.x += 5;

	BombEffect::BombEffect(transform_.position_);
	time++;

	data.position = transform_.position_;
	
	if (time >= 100)
	{
		KillMe();
	}

	if (IsReturn_)
	{
		transform_.position_.x--;
	}
	else
	{
		transform_.position_.x++;
	}

	if (starTime_ >= 7)
	{
		starTime_ = 0;
	}
	else if (starTime_ > 0)
	{
		starTime_++;
	}
}

//�`��
void Bomb::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Bomb::Release()
{
}

void Bomb::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "EnemyBlue" || 
		pTarget->GetObjectName() == "EnemyGreen" ||
		pTarget->GetObjectName() == "EnemyRed" ||
		pTarget->GetObjectName() == "Fire")
	{
		pTarget->KillMe();
	}
}