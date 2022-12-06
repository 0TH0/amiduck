#include "Player.h"
#include "Engine/Model.h"
//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1),pLine(nullptr)
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("box.fbx");
    assert(hModel_ >= 0);

    transform_.scale_ = XMFLOAT3(0.3, 0.3, 0.3);


    //ポリライン初期化
    pLine = new PoryLine;
    pLine->Load("tex.png");
}

//更新
void Player::Update()
{
    //ここはぐちゃぐちゃキューブを動かしてるだけ
    {
        XMVECTOR v = { 5.0f,0,0,0 };
        XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
        XMMATRIX rotZ = XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));

        v = XMVector3TransformCoord(v, rotY * rotZ);

        XMStoreFloat3(&transform_.position_, v);

        transform_.rotate_.y += 5.0f;
        transform_.rotate_.z += 3.0f;
    }


    //ポリラインに現在の位置を伝える
    pLine->AddPosition(transform_.position_);

}

//描画
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);


    //ポリラインを描画
    pLine->Draw();
}

//開放
void Player::Release()
{
    //ポリライン解放
    pLine->Release();
}