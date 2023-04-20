#include "FireFollowGround.h"
#include "Stage.h"
#include "PlayScene.h"
#include "StartScene.h"
#include "Star.h"
#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"

//コンストラクタ
FireFollowGround::FireFollowGround(GameObject* parent)
    :GameObject(parent, "FireFollowGround"),

    //変数
    hModel_(-1),
    jump_v0(0), gravity(0), angle(0), BossHp(3), hModelBlock_(-1),

    //フラグ
    IsJump(false), IsGround(false),

    //定数
    SPEED(0.6f), DUSHSPEED(0.05f),
    CAMERA_POS_Y(-15.0f), CAMERA_TAR_Y(-5.0f)
{
}

//デストラクタ
FireFollowGround::~FireFollowGround()
{
}

//初期化
void FireFollowGround::Initialize()
{
    hModel_ = Model::Load("Model\\fire_blue.fbx");
    assert(hModel_ >= 0);

    //位置
    transform_.rotate_ = XMFLOAT3(0, rotate_.y, 0);
    transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35);

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
    AddCollider(collision);

    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);

    pText->Initialize();

    pLine = new PoryLine;
    pLine->Load("Image\\line_white.png");
    assert(pLine != nullptr);

    Player* pPlayer = (Player*)FindObject("Player");
    PlayerPos_ = pPlayer->GetPosition();
    transform_.position_ = PlayerPos_;
}

void FireFollowGround::Update()
{
    time++;

    if (time >= 240)
    {
        KillMe();
    }

    pLine->AddPosition(transform_.position_);

    transform_.rotate_ = XMFLOAT3(0, rotate_.y, 0);

    pStage = (Stage*)FindObject("Stage");

    // 1フレーム前の座標
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);

    //////////////////壁との衝突判定///////////////////////
    int objX = transform_.position_.x;
    int objY = transform_.position_.y;
    int objZ = transform_.position_.z;

    ////壁の判定(上)
    if (pStage->IsWall(objX, objZ))
    {
        transform_.position_.y = (int)(transform_.position_.y) + 0.8;
        IsJump = 0;
    }
    if (pStage->IsBridge(objX, objZ))
    {
        transform_.position_.y = (int)(transform_.position_.y) + 0.8;
        IsJump = 0;
    }

    if (!a && !b && pStage->IsEmpty((float)objX + 3, objZ))
    {
        IsReturn = true;
    }
    if (!a && !b && pStage->IsEmpty((float)objX - 2.5, objZ))
    {
        IsReturn = false;
    }

    Player* pPlayer = (Player*)FindObject("Player");

    if (pPlayer->GetReturn())
    {
        transform_.position_.x -= SPEED;
    }
    else
    {
        transform_.position_.x += SPEED;
    }

    ///////////////////////// あみだくじの処理 ///////////////////////////////////////////

    if (!b && time2 > 4)
    {
        if (pStage->IsBridge(objX, objZ - 3))
        {
            SPEED = 0;
            a = true;
            time2 = 0;
        }
    }

    //右に行く
    if (a)
    {
        rotate_.y = -90;
        if (g <= 0)
        {
            s = 0.5;
            t += s;
            if (t >= 6)
            {
                trans[0].position_ = transform_.position_;
                time1 = 0;
                s = 0;
                t = 0;
                a = false;
                SPEED = 0.5;
            }
            else
            {
                transform_.position_.z -= s;
            }
        }
    }
    //左に行く
    else
    {
        time2++;

        if (!b) time1++;

        if (time1 > 4)
        {
            if (pStage->IsBridge(objX, objZ + 2))
            {
                SPEED = 0;
                b = true;
            }
        }

        if (b)
        {
            rotate_.y = 90;
            f = 0.5;
            g += f;
            if (g >= 6)
            {
                trans[1].position_ = transform_.position_;
                time2 = 0;
                g = 0;
                f = 0;
                b = false;
                SPEED = 0.5;
                time1 = 0;
            }
            else
            {
                transform_.position_.z += f;
            }
        }
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

void FireFollowGround::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    pLine->SetColor(XMFLOAT4(1, 0.6, 1, 0.7));
    pLine->Draw();
}

void FireFollowGround::Release()
{
    pLine->Release();
}

void FireFollowGround::OnCollision(GameObject* pTarget)
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
        KillMe();
    }
}