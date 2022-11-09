#include "Fire.h"
#include "Engine/Model.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Player.h"

//�R���X�g���N�^
Fire::Fire(GameObject* parent)
	: GameObject(parent, "Fire"), hModel_(-1)
{
}

//������
void Fire::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hModel_ = Model::Load("fire.fbx");
	assert(hModel_ >= 0);
}

//�X�V
void Fire::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");
	
	PlayerPosX_ = pPlayer->GetPosition().x;

	PlayerPosZ_ = pPlayer->GetPosition().z;

	if (Input::IsKeyDown(DIK_SPACE))
	{
		transform_.position_ = XMFLOAT3(PlayerPosX_, 0 ,PlayerPosZ_);
	}
}

//�`��
void Fire::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Fire::Release()
{
}

