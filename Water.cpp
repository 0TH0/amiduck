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
    hModel_ = Model::Load("Water\\water3.fbx");
    assert(hModel_ >= 0);
    transform_.position_ = { 5,-3 ,5 };
    transform_.scale_ = XMFLOAT3(24, 0.1, 24);
    Model::SetSahder(hModel_, Direct3D::SHADER_WATER);
}

//更新
void Water::Update()
{
    scroll_ += 0.0002f;

    Model::SetUvScroll(hModel_, scroll_);

}

//描画
void Water::Draw()
{
    transform_.scale_ = XMFLOAT3(24, 0.1, 24);
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Water::Release()
{
}