#include "Pipe.h"
#include "Block.h"
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"

//コンストラクタ
Pipe::Pipe(GameObject* parent)
    :GameObject(parent, "Pipe"), hModel_(-1)
{
}

//デストラクタ
Pipe::~Pipe()
{
}

//初期化
void Pipe::Initialize()
{
    /////////////モデルデータのロード////////////////////
    hModel_ = Model::Load("Pipe_Edge.fbx");
    assert(hModel_ >= 0);
}

//更新
void Pipe::Update()
{
}

//描画
void Pipe::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Pipe::Release()
{
}