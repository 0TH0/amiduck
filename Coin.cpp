#include "Coin.h"
#include "PlayScene.h"
#include "Player.h"

#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

//コンストラクタ
Coin::Coin(GameObject* parent)
	: GameObject(parent, "Coin")
{
}

//初期化
void Coin::Initialize()
{
	hModel_ = Model::Load("Coin\\coin.fbx");
	assert(hPict_ >= 0);

	//当たり判定
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
	AddCollider(collision);
}

//更新
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

	//ビューポート行列
	float w = (FLOAT)Direct3D::screenWidth_ / 2.0f;

	float h = (FLOAT)Direct3D::screenHeight_ / 2.0f;

	XMMATRIX vp = {
		w,  0, 0, 0,
		0, -h, 0, 0,
		0,  0, 1, 0,
		w,  h, 0, 1
	};

	//各行列の逆行列
	XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
	XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());
	XMMATRIX invPrj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());

	//マウス位置（手前）
	XMFLOAT3 mousePosFront = Input::GetMousePosition();
	mousePosFront.z = 0.0f;

	//マウス位置（奥）
	XMFLOAT3 mousePosBack = Input::GetMousePosition();
	mousePosBack.z = 1.0f;

	//逆行列の合成
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

//描画
void Coin::Draw()
{
	Model::SetTransform(hModel_, transform_);

	if (IsVisibled())
	{
		Model::Draw(hModel_);
	}
}

//開放
void Coin::Release()
{
}

void Coin::OnCollision(GameObject* pTarget)
{
	//敵に当たった
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