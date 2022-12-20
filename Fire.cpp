#include "Fire.h"
#include "Engine/Model.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Player.h"

//コンストラクタ
Fire::Fire(GameObject* parent)
	: GameObject(parent, "Fire"), hModel_(-1), pLine(nullptr)
{
}

//初期化
void Fire::Initialize()
{
	//画像データのロード
	hModel_ = Model::Load("Enemy\\raccoon10.fbx");
	assert(hModel_ >= 0);

	//当たり判定
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1.0f);
	AddCollider(collision);

    transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35);

    transform_.rotate_ = XMFLOAT3(0, 0, 0);

    //ポリライン初期化
    pLine = new PoryLine;
    pLine->Load("tex_red.png");

    pLine2 = new PoryLine;
    pLine2->Load("tex_orange.png");

    //初期位置はプレイヤーの位置のｙ＋１
    Player* pPlayer = (Player*)FindObject("Player");
    PlayerTrans_.position_ = pPlayer->GetPosition();
    transform_.position_ = PlayerTrans_.position_;
    transform_.position_.y = PlayerTrans_.position_.y + 1;
}

//更新
void Fire::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");
    transform_.rotate_.x += 5;

	time++;

	if (time >= 90)
	{
		KillMe();
	}
	else
	{
        transform_.position_.x++;
	}

    //ポリラインに現在の位置を伝える
    pLine->AddPosition(transform_.position_);
    pLine2->AddPosition(transform_.position_);
}

//描画
void Fire::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

    //ポリラインを描画
    //pLine->Draw();
    //pLine2->Draw();
}

//開放
void Fire::Release()
{
    //ポリライン解放
    pLine->Release();
    pLine2->Release();
}

void Fire::OnCollision(GameObject* pTarget)
{
	//敵に当たった
	if (pTarget->GetObjectName() == "Enemy")
	{
		pTarget->KillMe();
	}
}