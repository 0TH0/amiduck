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
	hModel_ = Model::Load("fire.fbx");
	assert(hModel_ >= 0);

	//当たり判定
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
	AddCollider(collision);

    transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35);

    transform_.rotate_ = XMFLOAT3(0, 90, 0);

    //ポリライン初期化
    pLine = new PoryLine;
    pLine->Load("tex_red.png");

    pLine2 = new PoryLine;
    pLine2->Load("tex_orange.png");

    Player* pPlayer = (Player*)FindObject("Player");
    PlayerPos_ = pPlayer->GetPosition();
    transform_.position_ = PlayerPos_;
}

//更新
void Fire::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");
    transform_.position_ = PlayerPos_;

	plus = 1;
	time++;

	if (Input::IsKeyDown(DIK_SPACE))
	{
		if (!Is)
		{
            PlayerPos_ = pPlayer->GetPosition();
			Is = true;
		}
	}

	if (time >= 90)
	{
		KillMe();
	}
	else
	{
		PlayerPos_.x += plus;
	}

    //ポリラインに現在の位置を伝える
    pLine->AddPosition(PlayerPos_);
    pLine2->AddPosition(PlayerPos_);

    ///////////////////////// あみだくじの処理 //////////////////////////////////////////
   
    //////////////////壁との衝突判定///////////////////////
    //int objX = transform_.position_.x;
    //int objY = transform_.position_.y;
    //int objZ = transform_.position_.z;
    //////壁の判定(上)
    //if (pStage->IsWall(objX, objY, objZ))
    //{
    //    transform_.position_.y = (int)(transform_.position_.y) + 0.8;
    //}
    //if (pStage->IsWallX(objX, objY, objZ))
    //{
    //    transform_.position_.y = (int)(transform_.position_.y) + 0.8;
    //}
    //if (!a && !b && pStage->IsEmpty((float)objX + 4, objY, objZ))
    //{
    //    IsReturn = true;
    //}
    //if (!a && !b && pStage->IsEmpty((float)objX - 2.5, objY, objZ))
    //{
    //    IsReturn = false;
    //}
    //if (IsReturn)
    //{
    //    transform_.position_.x -= speed_;
    //}
    //else
    //{
    //    transform_.position_.x += speed_;
    //}
    //if (!b && time2 > 4)
    //{
    //    if (pStage->IsWallM(objX, objY, objZ - 3))
    //    {
    //        speed_ = 0;
    //        a = true;
    //        time2 = 0;
    //    }
    //}
    ////右に行く
    //if (a)
    //{
    //    IsStop = false;
    //    if (g <= 0)
    //    {
    //        s = 0.2f;
    //        t += s;
    //        if (t >= 6)
    //        {
    //            trans[0].position_ = transform_.position_;
    //            time1 = 0;
    //            s = 0;
    //            t = 0;
    //            a = false;
    //            speed_ = 0.2;
    //        }
    //        else
    //        {
    //            transform_.position_.z -= s;
    //        }
    //    }
    //}
    ////左に行く
    //else
    //{
    //    //止まっていなかったら
    //    if (!IsStop)
    //    {
    //        time2++;
    //        if (!b) time1++;
    //    }
    //    if (time1 > 4)
    //    {
    //        if (pStage->IsPipe(objX, objY, objZ + 2))
    //        {
    //            speed_ = 0;
    //            b = true;
    //        }
    //    }
    //    if (b)
    //    {
    //        IsStop = false;
    //        f = 0.2f;
    //        g += f;
    //        if (g >= 6)
    //        {
    //            trans[1].position_ = transform_.position_;
    //            time2 = 0;
    //            g = 0;
    //            f = 0;
    //            b = false;
    //            speed_ = 0.2;
    //            time1 = 0;
    //        }
    //        else
    //        {
    //            transform_.position_.z += f;
    //        }
    //    }
    //}
}

//描画
void Fire::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

    //ポリラインを描画
    pLine->Draw();
    pLine2->Draw();
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