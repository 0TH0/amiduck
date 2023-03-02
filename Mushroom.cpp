#include "Mushroom.h"
#include "Engine/Model.h"

//コンストラクタ
Mushroom::Mushroom(GameObject* parent)
	: GameObject(parent, "Mushroom"), hModel_(-1)
{
}

//初期化
void Mushroom::Initialize()
{
	hModel_ = Model::Load("Model\\fire\\fireball.fbx");
	assert(hModel_ >= 0);

	transform_.position_ = XMFLOAT3(29, 1, 32);
	transform_.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5f);

	//当たり判定
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
	AddCollider(collision);

	pParticle_ = Instantiate<Particle>(this);

	//炎
	{
		EmitterData data;

		//炎
		/*data.textureFileName = "Image\\Cloud.png";
		
		data.positionErr = XMFLOAT3(0.1, 0, 0.1);
		data.delay = 5;
		data.number = 1;
		data.lifeTime = 60;
		data.gravity = -0.002f;
		data.dir = XMFLOAT3(0, 1, 0);
		data.dirErr = XMFLOAT3(0, 0, 0);
		data.speed = 0.01f;
		data.speedErr = 0.0;
		data.size = XMFLOAT2(1.5, 1.5);
		data.sizeErr = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(1.01, 1.01);
		data.color = XMFLOAT4(1, 1, 0, 1);
		data.deltaColor = XMFLOAT4(0, -0.03, 0, -0.02);*/

		//for (int i = 0; i < 5; i++)
		{
			transform_.position_ = XMFLOAT3(29, 1, 32);
			//data.position = transform_.position_;

			//pParticle_->Start(data);
		}

		//火の粉
	/*	data.number = 3;
		data.positionErr = XMFLOAT3(0.8, 0, 0.8);
		data.dir = XMFLOAT3(0, 1, 0);
		data.dirErr = XMFLOAT3(10, 10, 10);
		data.size = XMFLOAT2(0.2, 0.2);
		data.scale = XMFLOAT2(0.95, 0.95);
		data.lifeTime = 120;
		data.speed = 0.1f;
		data.gravity = 0;
		pParticle_->Start(data);*/
	}
}

//更新
void Mushroom::Update()
{
	transform_.rotate_.y += 5;
}

//描画
void Mushroom::Draw()
{
	//for (int i = 0; i < 5; i++)
	{
		transform_.position_ = XMFLOAT3(29, 1, 32);
		transform_.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5f);
		Model::SetTransform(hModel_, transform_);
		Model::Draw(hModel_);
	}
}

//開放
void Mushroom::Release()
{
}