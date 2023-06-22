#include "Fire.h"
#include "Engine/Model.h"
#include "Player.h"

//コンストラクタ
Fire::Fire(GameObject* parent)
	: GameObject(parent, "Fire"), hModel_(-1)
{
}

//初期化
void Fire::Initialize()
{
	hModel_ = Model::Load("Model\\fire\\fireball.fbx");
	assert(hModel_ >= 0);
	//当たり判定
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 2.f);
	AddCollider(collision);
}

//更新
void Fire::Update()
{
    Stage* pStage = (Stage*)FindObject("Stage");

    for (int x = 0; x < STAGE_SIZE_X; x++)
    {
        for (int z = 0; z < STAGE_SIZE_Z; z++)
        {
            AI_.SetMapType(pStage->GetStageType(x, z), x, z);
        }
    }

	//回す
	transform_.position_ = Transform::RotateAround(trans.position_, 10.f, 2.f, right_);

	transform_.rotate_.y += 5;

    Player* pPlayer = (Player*)FindObject("Player");

    if (CanMove_)
    {
        if (totalCell >= 0)
        {
            XMVECTOR v = { AI_.GetToGoalCell(totalCell).x, 1.5f, AI_.GetToGoalCell(totalCell).z, 0 };

            XMStoreFloat3(&trans.position_, XMVectorLerp(XMLoadFloat3(&trans.position_), v, 0.2f));

            trans.position_ = VectorToFloat3(v);
        }
    }

    //何フレーム毎に進むか
    int frame = 7;

    if (count_ > frame)
    {
        int PlayerPosX = (int)pPlayer->GetPosition().x;
        int PlayerPosZ = (int)pPlayer->GetPosition().z;

        //プレイヤーを探索
        if (AI_.Search({ (int)trans.position_.x, (int)trans.position_.z }, { PlayerPosX, PlayerPosZ }))
        {
            totalCell = AI_.GetToGoalTotalCell();
            CanMove_ = true;
        }

        count_ = 0;
    }
    count_++;
}

//描画
void Fire::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Fire::Release()
{
}