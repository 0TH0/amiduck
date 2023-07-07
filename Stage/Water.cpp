#include "Water.h"
#include "../Engine/Model.h"

namespace
{
    static const float SCROOL = 0.0001f; //1フレームで動かす量
    static const XMFLOAT3 pos = { 0,-3,0 };
}

//コンストラクタ
Water::Water(GameObject* parent)
    :GameObject(parent, "Water"), hModel_(-1),scroll_(0.f)
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
    hModel_ = Model::Load("Water\\water.fbx");
    assert(hModel_ >= 0);
    transform_.position_.y = pos.y;
    Model::SetSahder(hModel_, Direct3D::SHADER_WATER);
}

//更新
void Water::Update()
{
    scroll_ += SCROOL;
    Model::SetUvScroll(hModel_, scroll_);
}

//描画
void Water::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Water::Release()
{
}