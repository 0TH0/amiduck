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
	hModel_ = Model::Load("Model\\Player\\egg.fbx");
	assert(hModel_ >= 0);

	transform_.position_ = XMFLOAT3(29, 1, 32);
	transform_.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5f);

	//当たり判定
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
	AddCollider(collision);
}

//更新
void Mushroom::Update()
{
}

//描画
void Mushroom::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Mushroom::Release()
{
}