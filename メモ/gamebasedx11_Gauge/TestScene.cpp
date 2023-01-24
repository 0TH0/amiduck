#include "TestScene.h"

#include "Engine/Input.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene"), pGauge_(nullptr)
{
}

//初期化
void TestScene::Initialize()
{
	pGauge_ = Instantiate<Gauge>(this);
}

//更新
void TestScene::Update()
{
	if (Input::IsKeyDown(DIK_LEFT))
	{
		pGauge_->Damage(rand() %100+20);
	}

	if (Input::IsKeyDown(DIK_RIGHT))
	{
		pGauge_->Recovery(rand() % 100+20);
	}
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
