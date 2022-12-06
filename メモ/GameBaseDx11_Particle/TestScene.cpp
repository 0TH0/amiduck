#include "TestScene.h"
#include "Engine/Model.h"

#include "Engine/Camera.h"
#include "Engine/Input.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene"), hModel_(-1)
{
}

//初期化
void TestScene::Initialize()
{
	Camera::SetPosition(XMFLOAT3(0, 10, -15));
	Camera::SetTarget(XMFLOAT3(0, 0, 0));
	hModel_ = Model::Load("Ground.fbx");

	pParticle_ = Instantiate<Particle>(this);

	//炎
	{
		EmitterData data;

		//炎
		data.textureFileName = "Cloud.png";
		data.position = XMFLOAT3(-4, 1.5, -4);
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
		data.deltaColor = XMFLOAT4(0, -0.03, 0, -0.02);
		pParticle_->Start(data);

		//火の粉
		data.number = 3;
		data.positionErr = XMFLOAT3(0.8, 0, 0.8);
		data.dir = XMFLOAT3(0, 1, 0);
		data.dirErr = XMFLOAT3(10, 10, 10);
		data.size = XMFLOAT2(0.2, 0.2);
		data.scale = XMFLOAT2(0.95, 0.95);
		data.lifeTime = 120;
		data.speed = 0.1f;
		data.gravity = 0;
		pParticle_->Start(data);
	}


	//煙
	{
		EmitterData data;

		data.textureFileName = "Cloud.png";
		data.position = XMFLOAT3(4, 1.5, 4);
		data.positionErr = XMFLOAT3(0.1, 0, 0.1);
		data.delay = 5;
		data.number = 1;
		data.lifeTime = 150;
		data.dir = XMFLOAT3(0, 1, 0);
		data.dirErr = XMFLOAT3(0, 0, 0);
		data.speed = 0.1f;
		data.accel = 0.98;
		data.speedErr = 0.0;
		data.size = XMFLOAT2(2, 2);
		data.sizeErr = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(1.01, 1.01);
		data.color = XMFLOAT4(1, 1, 1, 0.2);
		data.deltaColor = XMFLOAT4(0, 0, 0, -0.002);
		pParticle_->Start(data);
	}

	//水
	{
		EmitterData data;

		data.textureFileName = "Water.png";
		data.position = XMFLOAT3(4, 3.3, -4.5);
		data.delay = 1;
		data.number = 3;
		data.lifeTime = 50;
		data.dir = XMFLOAT3(0,0,-1);
		data.dirErr = XMFLOAT3(0, 0, 0);
		data.gravity = 0.005;
		data.speed = 0.1f;
		data.accel = 0.98;
		data.speedErr = 0.0;
		data.size = XMFLOAT2(1, 1);
		data.sizeErr = XMFLOAT2(0.8, 0.4);
		data.scale = XMFLOAT2(1.02, 1.02);
		data.color = XMFLOAT4(1, 1, 1, 0.1);
		pParticle_->Start(data);

		//水滴
		data.textureFileName = "buble.png";
		data.position = XMFLOAT3(4, 3.3, -4.5);
		data.positionErr = XMFLOAT3(0.5, 0, 0);
		data.delay = 1;
		data.number = 3;
		data.lifeTime = 50;
		data.dir = XMFLOAT3(0, 0, -1);
		data.dirErr = XMFLOAT3(0, 20, 0);
		data.gravity = 0.005;
		data.speed = 0.1f;
		data.accel = 0.98;
		data.speedErr = 0.0;
		data.size = XMFLOAT2(0.3, 0.3);
		data.sizeErr = XMFLOAT2(0, 0);
		data.scale = XMFLOAT2(0.98, 0.98);
		data.color = XMFLOAT4(1, 1, 1, 1);
		pParticle_->Start(data);
	}



}

//更新
void TestScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		EmitterData data;
		data.textureFileName = "Cloud.png";
		data.position = XMFLOAT3(0,0.05,0);
		data.delay = 0;
		data.number = 80;
		data.lifeTime = 20;
		data.dir = XMFLOAT3(0, 1, 0);
		data.dirErr = XMFLOAT3(90, 90, 90);
		data.speed = 0.1f;
		data.speedErr = 0.8;
		data.size = XMFLOAT2(1, 1);
		data.sizeErr = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(1.05, 1.05);
		data.color = XMFLOAT4(1, 1, 0.1, 1);
		data.deltaColor = XMFLOAT4(0, -1.0/20, 0, -1.0/20);
		pParticle_->Start(data);





		data.delay = 0;
		data.number = 80;
		data.lifeTime = 100;
		data.positionErr = XMFLOAT3(0.5, 0, 0.5);
		data.dir = XMFLOAT3(0, 1, 0);
		data.dirErr = XMFLOAT3(90, 90, 90);
		data.speed = 0.25f;
		data.speedErr = 1;
		data.accel = 0.93;
		data.size = XMFLOAT2(0.1, 0.1);
		data.sizeErr = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(0.99, 0.99);
		data.color = XMFLOAT4(1, 1, 0.1, 1);
		data.deltaColor = XMFLOAT4(0, 0, 0, 0);
		data.gravity = 0.003f;
		pParticle_->Start(data);





	}

}

//描画
void TestScene::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void TestScene::Release()
{
}
