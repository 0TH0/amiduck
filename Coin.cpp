#include "Coin.h"
#include "PlayScene.h"
#include "Player.h"

#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
Coin::Coin(GameObject* parent)
	: GameObject(parent, "Coin")
{
}

//������
void Coin::Initialize()
{
	hModel_ = Model::Load("Coin\\coin.fbx");
	assert(hPict_ >= 0);

	//�����蔻��
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
	AddCollider(collision);
}

//�X�V
void Coin::Update()
{
	transform_.rotate_.y += 3;

	if (IsHit_)
	{
		time_++;
	}

	if (time_ >= 300)
	{
		Visible();
		IsHit_ = false;
		time_ = 0;
	}

	//�r���[�|�[�g�s��
	float w = (FLOAT)Direct3D::screenWidth_ / 2.0f;

	float h = (FLOAT)Direct3D::screenHeight_ / 2.0f;

	XMMATRIX vp = {
		w,  0, 0, 0,
		0, -h, 0, 0,
		0,  0, 1, 0,
		w,  h, 0, 1
	};

	//�e�s��̋t�s��
	XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
	XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());
	XMMATRIX invPrj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());

	//�}�E�X�ʒu�i��O�j
	XMFLOAT3 mousePosFront = Input::GetMousePosition();
	mousePosFront.z = 0.0f;

	//�}�E�X�ʒu�i���j
	XMFLOAT3 mousePosBack = Input::GetMousePosition();
	mousePosBack.z = 1.0f;

	//�t�s��̍���
	XMMATRIX invTransform = invVP * invPrj * invView;

	XMVECTOR vStart = XMVector3TransformCoord(XMLoadFloat3(&mousePosFront), invTransform);
	XMVECTOR vTarget = XMVector3TransformCoord(XMLoadFloat3(&mousePosBack), invTransform);

	RayCastData rCoin;
	Model::RayCast(hModel_, &rCoin);

	if (rCoin.hit)
	{
		transform_.position_.y++;
	}
}

//�`��
void Coin::Draw()
{
	Model::SetTransform(hModel_, transform_);

	if (IsVisibled())
	{
		Model::Draw(hModel_);
	}
}

//�J��
void Coin::Release()
{
}

void Coin::OnCollision(GameObject* pTarget)
{
	//�G�ɓ�������
	if (pTarget->GetObjectName() == "Player")
	{
		Player* pPlayer = (Player*)FindObject("Player");

		if (IsVisibled())
		{
			//pPlayer->PlusCoinCount(1);
		}

		Invisible();
		IsHit_ = true;
	}
}