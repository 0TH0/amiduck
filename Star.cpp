#include "Star.h"
#include "PlayScene.h"
#include "Player.h"

#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

//コンストラクタ
Star::Star(GameObject* parent)
	: GameObject(parent, "Star")
{
}

//初期化
void Star::Initialize()
{
	hModel_ = Model::Load("Model\\star.fbx");
	assert(hPict_ >= 0);

	//当たり判定
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
	AddCollider(collision);

	transform_.scale_ = XMFLOAT3(0.1f, 0.1f, 0.1f);

	pParticle_ = Instantiate<Particle>(this);
}

//更新
void Star::Update()
{
	transform_.rotate_.y += 3;
	
	if (time_ <= 60)
	{
		time_++;
	}

	//if (IsHit_)
	//{
	//	time_++;
	//}

	//if (time_ >= 300)
	//{
	//	Visible();
	//	IsHit_ = false;
	//	time_ = 0;
	//}
	if (transform_.position_.y <= 1.25f)
	{
		transform_.position_.y = 1.25f;
	}
	else
	{
		transform_.position_.y -= 0.05f;
	}
	if (!IsVisibled() && time_ >= 60)
	{
		KillMe();
	}
}

//描画
void Star::Draw()
{
	Model::SetTransform(hModel_, transform_);

	if (IsVisibled())
	{
		Model::Draw(hModel_);
	}
}

//開放
void Star::Release()
{
}

void Star::OnCollision(GameObject* pTarget)
{
	//敵に当たった
	if (pTarget->GetObjectName() == "Player" || pTarget->GetObjectName() == "Enemy")
	{
		if (time_ >= 60 && IsVisibled())
		{
			Invisible();
			StarEffect();
			time_ = 0;
		}
	}
}

void Star::StarEffect()
{
	EmitterData data;
	data.textureFileName = "Image\\star.png";
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