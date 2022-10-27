#include "Block.h"
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"

//コンストラクタ
Block::Block(GameObject* parent)
    :GameObject(parent, "Block"), hModel_(-1)
{
}

//デストラクタ
Block::~Block()
{
}

//初期化
void Block::Initialize()
{
    /////////////モデルデータのロード////////////////////
    BoxCollider* collision = new BoxCollider(XMFLOAT3(0.5f, 0.5f, 0), XMFLOAT3(1, 1, 0));
    AddCollider(collision);

    hModel_ = Model::Load("log.fbx");
    assert(hModel_ >= 0);
}

//更新
void Block::Update()
{
}

//描画
void Block::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Block::Release()
{
}