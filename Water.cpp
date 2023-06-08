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
    hModel_ = Model::Load("Water\\water.fbx");
    assert(hModel_ >= 0);
    transform_.position_ = { 10,0,10 };
    transform_.scale_ = XMFLOAT3(500, 0.1, 500);
    Model::SetSahder(hModel_);
}

static float scroll;

//更新
void Water::Update()
{
    transform_.rotate_.y += 0.05f;
    scroll += 0.002f;

    Model::SetUvScroll(hModel_, scroll);

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