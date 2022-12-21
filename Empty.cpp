#include "Empty.h"
#include "TestScene.h"
#include "Engine/Model.h"

//コンストラクタ
Empty::Empty(GameObject* parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void Empty::Initialize()
{
	hModel_ = Model::Load("Empty.fbx");
	assert(hModel_ >= 0);
}

//更新
void Empty::Update()
{
}

//描画
void Empty::Draw()
{
	//Model::SetTransform(hModel_, transform_);
	//Model::Draw(hModel_);
}

//開放
void Empty::Release()
{
}
