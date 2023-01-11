#include "ItemBox.h"
#include "PlayScene.h"
#include "Player.h"

#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

//コンストラクタ
ItemBox::ItemBox(GameObject* parent)
	: GameObject(parent, "ItemBox")
{
}

//初期化
void ItemBox::Initialize()
{
	hModel_ = Model::Load("Model\\itemBox.fbx");
	assert(hPict_ >= 0);

	//当たり判定
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
	AddCollider(collision);

	pParticle_ = Instantiate<Particle>(this);
}

//更新
void ItemBox::Update()
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
	};

	//RayCastData rDog;
	//Camera::CalcScreenToWorld(rDog);
	//Model::RayCast(hModel_, &rDog);

	//if (rDog.hit)
	//{
	//	transform_.position_.y++;
	//}
}

//描画
void ItemBox::Draw()
{
	Model::SetTransform(hModel_, transform_);

	if (IsVisibled())
	{
		Model::Draw(hModel_);
	}
}

//開放
void ItemBox::Release()
{
}

void ItemBox::OnCollision(GameObject* pTarget)
{
	//敵に当たった
	if (pTarget->GetObjectName() == "Player")
	{
		Player* pPlayer = (Player*)FindObject("Player");

		if (IsVisibled())
		{
			StarEffect();
		}

		Invisible();
		IsHit_ = true;
	}
}

void ItemBox::StarEffect()
{
	EmitterData data;
	data.textureFileName = "Image\\question_white.png";
	data.position = transform_.position_;
	data.delay = 0;
	data.number = 80;
	data.lifeTime = 100;
	data.positionErr = XMFLOAT3(0.4, 0, 0.4);
	data.dir = XMFLOAT3(0, 1, 0);
	data.dirErr = XMFLOAT3(90, 90, 90);
	data.speed = 0.25f;
	data.speedErr = 1;
	data.accel = 0.93;
	data.size = XMFLOAT2(0.4, 0.4);
	data.sizeErr = XMFLOAT2(0.4, 0.4);
	data.scale = XMFLOAT2(1, 1);
	data.color = XMFLOAT4(1, 1, 1, 1);
	data.deltaColor = XMFLOAT4(0, 0, 0, 0);
	data.gravity = 0.003f;
	pParticle_->Start(data);
}
