#include "Fire.h"
#include "Engine/Model.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Player.h"
#include "Engine/Global.h"
#include "Star.h"
#include "Enemy.h"

//コンストラクタ
Fire::Fire(GameObject* parent)
	: GameObject(parent, "Fire"), hModel_(-1), pLine(nullptr)
{
}

Fire::~Fire()
{
	SAFE_DELETE(pLine);
	SAFE_DELETE(pLine2);
}

//初期化
void Fire::Initialize()
{
	//画像データのロード
	hModel_ = Model::Load("Model\\Enemy\\raccoon.fbx");
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

	if(pPlayer->GetReturn())
	{
        transform_.position_.x--;
	}
	else
	{
		transform_.position_.x++;
	}

    //ポリラインに現在の位置を伝える
    pLine->AddPosition(transform_.position_);
    pLine2->AddPosition(transform_.position_);

	if (starTime_ >= 7)
	{
		starTime_ = 0;
	}
	else if (starTime_ > 0)
	{
		starTime_++;
	}
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
		pTarget->Invisible();

		if (starTime_ == 0)
		{
			starTime_++;
			Star* pStar = Instantiate<Star>(GetParent());
			Enemy* pEnemy = (Enemy*)FindObject("Enemy");
			pStar->SetPosition(pEnemy->GetPosition().x, pEnemy->GetPosition().y + 4, pEnemy->GetPosition().z);
		}
	}
}