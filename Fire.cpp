#include "Fire.h"
#include "Engine/Model.h"
#include "Player.h"

//コンストラクタ
Fire::Fire(GameObject* parent)
	: GameObject(parent, "Fire"), hModel_(-1)
{
}

//初期化
void Fire::Initialize()
{
	hModel_ = Model::Load("Model\\fire.fbx");
	assert(hModel_ >= 0);
	//当たり判定
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 2.f);
	AddCollider(collision);

	transform_.position_ = XMFLOAT3(5, 2, 5);
}

//更新
void Fire::Update()
{
	//回す
	transform_.position_ = Transform::RotateAround(transform_.position_, 0.2f, 3.f, right_);
	transform_.position_.x += 0.1f;
	transform_.rotate_.y += 5;
}

//描画
void Fire::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Fire::Release()
{
}