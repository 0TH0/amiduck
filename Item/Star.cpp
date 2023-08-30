#include "Star.h"
#include "../Scene/PlayScene.h"
#include "../Player/Player.h"
#include "../Manager/StarEffect.h"
#include "../Engine/Model.h"
#include "../Engine/Image.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"

//�R���X�g���N�^
Star::Star(GameObject* parent)
	: GameObject(parent, "Star"),scale_(0.15f),MAX_TIME(60), rotateSpeed_(3.f), rimit_(10), gravity_(0.05f), rimitY(1.5f)
{
}

//������
void Star::Initialize()
{
	hModel_ = Model::Load("Model\\star_white.fbx");
	assert(hPict_ >= 0);

	//�����蔻��
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.75f);
	AddCollider(collision);

	transform_.position_.y = 5;
	transform_.scale_ = { scale_, scale_, scale_ };
}

//�X�V
void Star::Update()
{
	transform_.rotate_.y += rotateSpeed_;

	//�o�����ɃG�t�F�N�g���o��
	if (time_ < 2)
	{
		//StarManager::StarAudio();
		StarManager::StarEffect(transform_.position_);
	}

	//�J�n���Ă��璼���ɐ������Ȃ��悤��
	if (time_ <= MAX_TIME)
	{
		time_++;
	}
	//�n�ʂɒ�������
	if (transform_.position_.y <= rimitY)
	{
		transform_.position_.y = rimitY;
	}
	else
	{
		transform_.position_.y -= gravity_;
	}
	//�����銎��1�b�o������
	if (!IsVisibled() && time_ >= MAX_TIME)
	{
		KillMe();
	}
}

//�`��
void Star::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::SetColor(hModel_, XMFLOAT4(1, 1, 0, 1));
	Model::Draw(hModel_);
}

//�J��
void Star::Release()
{
}

void Star::OnCollision(GameObject* pTarget)
{
	//��������
	if (pTarget->GetObjectName() == "Player")
	{
		if (time_ >= rimit_ && IsVisibled())
		{
			Invisible();
			StarManager::StarEffect(transform_.position_);
			//StarManager::StarAudio();
			time_ = 0;
		}
	}
}