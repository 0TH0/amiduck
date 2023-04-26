#include "Duck.h"
#include "Engine/Model.h"

//コンストラクタ
Duck::Duck(GameObject* parent)
    :GameObject(parent, "Duck"), hModel_(-1)
{
}

//デストラクタ
Duck::~Duck()
{
}

//初期化
void Duck::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Model\\Player\\duck.fbx");
    assert(hModel_ >= 0);
    transform_.scale_ = XMFLOAT3(5, 5, 5);
    transform_.position_ = XMFLOAT3(300, 1, 50);
}

//更新
void Duck::Update()
{
    //transform_.rotate_.y += 1.0f;
}

//描画
void Duck::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Duck::Release()
{
}