#include "Water.h"
#include "Engine/Model.h"

//コンストラクタ
Water::Water(GameObject* parent)
    :GameObject(parent, "Water"), hModel_(-1)
{
}

//デストラクタ
Water::~Water()
{
}

//初期化
void Water::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Water\\Water.fbx");
    assert(hModel_ >= 0);
    transform_.scale_ = XMFLOAT3(10000, 10, 1000);
    transform_.position_ = XMFLOAT3(20, -2, 30);
}

//更新
void Water::Update()
{
    //transform_.rotate_.y += 1.0f;
}

//描画
void Water::Draw()
{
    Model::SetSahder(hModel_, Direct3D::SHADER_WATER);
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Water::Release()
{
}