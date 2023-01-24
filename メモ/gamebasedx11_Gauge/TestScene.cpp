#include "TestScene.h"

#include "Engine/Input.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene"), pGauge_(nullptr)
{
}

//������
void TestScene::Initialize()
{
	pGauge_ = Instantiate<Gauge>(this);
}

//�X�V
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

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}
