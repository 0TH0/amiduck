#include "Bomb.h"
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
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 3.f);
	AddCollider(collision);

	transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35);

	transform_.rotate_ = XMFLOAT3(0, 0, 0);
}

XMVECTOR player;
XMVECTOR mouse;
//�X�V
void Bomb::Update()
{
	if (Input::IsKey(DIK_O))
	{
		Player* pPlayer = (Player*)FindObject("Player");
		playerPos_ = pPlayer->GetPosition();
		playerPos_.y = 3;
		transform_.position_ = playerPos_;
		player = XMLoadFloat3(&playerPos_);


		//�����ʒu�̓v���C���[�̈ʒu�̂��{�P
		pStage = (Stage*)FindObject("Stage");
		mousePos_ = XMFLOAT3(pStage->GetMousePos().x, 3, pStage->GetMousePos().z);

		mouse = XMLoadFloat3(&mousePos_);
	}
	else
	{
		XMVECTOR Root = (mouse - player);

		//���K������
		Root = XMVector3Normalize(Root);//�x�N�g���̒������P�ɂ���

		XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) + Root);
		transform_.position_.y = 3;
	}
	//transform_.rotate_.x += 5;
	//time_++;
	//
	//if (time_ >= MAX_TIME)
	//{
	//	KillMe();
	//}
	//if (IsReturn_)
	//{
	//	transform_.position_.x--;
	//}
	//else
	//{
	//	transform_.position_.x++;
	//}
	//if (starDelay_ >= MAX_STAR_DELAY)
	//{
	//	starDelay_ = 0;
	//}
	//else if (starDelay_ > 0)
	//{
	//	starDelay_++;
	//}
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