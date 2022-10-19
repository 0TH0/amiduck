#include "Pipe_Base.h"
#include "Block.h"
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"

//コンストラクタ
Pipe_base::Pipe_base(GameObject* parent)
    :GameObject(parent, "Pipe_base"), hModel_(-1)
{
}

//デストラクタ
Pipe_base::~Pipe_base()
{
}

//初期化
void Pipe_base::Initialize()
{
    /////////////モデルデータのロード////////////////////
    BoxCollider* collision = new BoxCollider(XMFLOAT3(0.0f, 0.5f, 0), XMFLOAT3(1, 1, 0));
    AddCollider(collision);

    hModel_ = Model::Load("Pipe_Base.fbx");
    assert(hModel_ >= 0);
}

//更新
void Pipe_base::Update()
{
}

//描画
void Pipe_base::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Pipe_base::Release()
{
}