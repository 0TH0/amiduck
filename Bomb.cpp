#include "Bomb.h"
#include "Engine/Model.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Player.h"
#include "Engine/Global.h"
#include "Star.h"
#include "Enemy.h"

//コンストラクタ
Bomb::Bomb(GameObject* parent)
	: GameObject(parent, "Bomb"), hModel_(-1)
{
}

Bomb::~Bomb()
{
}

//初期化
void Bomb::Initialize()
{
	//画像データのロード
	hModel_ = Model::Load("Model\\bomb.fbx");
	assert(hModel_ >= 0);

	//当たり判定
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.5f);
	AddCollider(collision);

	transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35);

	transform_.rotate_ = XMFLOAT3(0, 0, 0);

	//初期位置はプレイヤーの位置のｙ＋１
	Player* pPlayer = (Player*)FindObject("Player");
	PlayerTrans_.position_ = pPlayer->GetPosition();
	transform_.position_ = PlayerTrans_.position_;
	transform_.position_.y = PlayerTrans_.position_.y + 1;

	pParticle_ = Instantiate<Particle>(this);

	data.textureFileName = "Particle\\Cloud.png";
	data.delay = 0;
	data.number = 5;
	data.lifeTime = 50;
	data.dir = XMFLOAT3(1, 0, 0);
	data.dirErr = XMFLOAT3(180, 90, 90);
	data.speed = 0.1f;
	data.speedErr = 1;
	data.size = XMFLOAT2(1, 0.5);
	data.sizeErr = XMFLOAT2(0.4, 0.4);
	data.scale = XMFLOAT2(1.01, 1.01);
	data.color = XMFLOAT4(1, 0, 0, 1);
	data.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);
	data.gravity = 0.003f;
	data.color = XMFLOAT4(0.5, 0.5, 0, 1);
}

//更新
void Bomb::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");
	transform_.rotate_.x += 5;

	time++;

	data.position = transform_.position_;
	pParticle_->Start(data);

	if (time >= 100)
	{
		KillMe();
	}

	if (pPlayer->GetReturn())
	{
		transform_.position_.x--;
	}
	else
	{
		transform_.position_.x++;
	}

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
void Bomb::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Bomb::Release()
{
}

void Bomb::OnCollision(GameObject* pTarget)
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