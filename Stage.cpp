#include "Stage.h"
#include "Player.h"
#include "PlayScene.h"
#include "Enemy.h"
#include "Player.h"
#include "Coin.h"
#include "Empty.h"

#include "Engine/SceneManager.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"
#include "Engine/Input.h"
#include "Engine/SphereCollider.h"
#include "Engine/BoxCollider.h"
#include "Engine/Camera.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{

}

//デストラクタ
Stage::~Stage()
{
}

void Stage::StageLoad()
{
    //空箱
    //hModel_[empty] = Model::Load("Empty.fbx");
    //assert(hModel_[0] >= 0);

    //ブロック
    hModel_[log] = Model::Load("log.fbx");
    assert(hModel_[log] >= 0);

    //旗先端
    hModel_[coin] = Model::Load("wood2.fbx");
    assert(hModel_[coin] >= 0);

    hModel_[enemy] = Model::Load("log.fbx");
    assert(hModel_[enemy] >= 0);

    hModel_[player] = Model::Load("log.fbx");
    assert(hModel_[player] >= 0);
}

void Stage::Cloud()
{
    data.textureFileName = "Particle\\Cloud.png";
    data.positionErr = XMFLOAT3(0.1, 0, 0.1);
    data.delay = 0;
    data.number = 5;
    data.lifeTime = 60;
    data.dir = XMFLOAT3(0, 1, 0);
    data.dirErr = XMFLOAT3(0, 0, 0);
    data.speed = 0.01f;
    data.speedErr = 0.5;
    data.size = XMFLOAT2(2, 2);
    data.sizeErr = XMFLOAT2(0.4, 0.4);
    data.scale = XMFLOAT2(1.03, 1.02);
    float color = 0.5;
    data.color = XMFLOAT4(color, color, color, 0.1);
    pParticle_->Start(data);
}

void Stage::SetCloudPos(float x, float y, float z)
{
    data.position.x = x;
    data.position.y = y;
    data.position.z = z;
}

//初期化
void Stage::Initialize()
{
    for (int x = 0; x < STAGE_SIZE_X; x++)
    {
        for (int z = 0; z < STAGE_SIZE_Z; z++)
        {
            stage_[x][z].height = 1;
            stage_[x][z].type = 0;
        }
    }

    StageLoad();

    //Csv読み込み
    CsvReader csv;
    csv.Load("map.csv");

    for (int x = 0; x < STAGE_SIZE_X; x++)
    {
        for (int z = 0; z < STAGE_SIZE_Z; z++)
        {
            stage_[x][z].type = csv.GetValue(x, -z + 38);

            if (stage_[x][z].type == empty)
            {
                //Empty* pEmpty = Instantiate<Empty>(this);
            }

            //コイン登場
            if (stage_[x][z].type == coin)
            {
                Coin* pCoin = Instantiate<Coin>(GetParent());
                pCoin->SetPosition(x + 0.25, 1, z + 1);
            }

            //エネミー登場
            if (stage_[x][z].type == enemy)
            {
                Enemy* pEnemy = Instantiate<Enemy>(GetParent());
                pEnemy->SetPosition(x, 1, z + 1);
            }

            //プレイヤー登場
            if (stage_[x][z].type  == player)
            {
                Player* pPlayer = Instantiate<Player>(GetParent());
                pPlayer->SetPosition(x, 1, z + 1);
            }
        }
    }

    pText->Initialize();
    pParticle_ = Instantiate<Particle>(this);
}
//更新
void Stage::Update()
{
    Player* pPlayer = (Player*)FindObject("Player");

    if (!pPlayer->GetReturn()) player_pos_.x = (int)pPlayer->GetPosition().x + 1;
    else player_pos_.x = (int)pPlayer->GetPosition().x - 1;

    player_pos_.z = (int)pPlayer->GetPosition().z;

    //time_++;

    //if (time_ == STAGE_SIZE_X)
    //{
    //    count_++;
    //    time_ = 0;
    //}

    //if (count_ >= 3)
    //{
    //    count_ = 3;
    //}

    //if (count_ > 0)
    //{
    //    if (Input::IsKeyDown(DIK_A))
    //    {
    //        map_[(int)player_pos_.x][0][(int)player_pos_.z + 2] = 2;
    //        map_[(int)player_pos_.x][0][(int)player_pos_.z + 3] = 2;
    //        map_[(int)player_pos_.x][0][(int)player_pos_.z + 4] = 2;
    //        time_ = 0;
    //        count_--;
    //        SetCloudPos(player_pos_.x, player_pos_.y + 1, player_pos_.z + 4);
    //        Cloud();
    //    }

    //    if (Input::IsKeyDown(DIK_D))
    //    {
    //        if ((int)player_pos_.z >= 38)
    //        {
    //            map_[(int)player_pos_.x][0][(int)player_pos_.z - 3] = 2;
    //            map_[(int)player_pos_.x][0][(int)player_pos_.z - 4] = 2;
    //            map_[(int)player_pos_.x][0][(int)player_pos_.z - 5] = 2;
    //            time_ = 0;
    //            count_--;
    //            SetCloudPos(player_pos_.x, player_pos_.y + 1, player_pos_.z - 3);
    //            Cloud();
    //        }
    //        else
    //        {
    //            if (Input::IsKeyDown(DIK_D))
    //            {
    //                map_[(int)player_pos_.x][0][(int)player_pos_.z - 2] = 2;
    //                map_[(int)player_pos_.x][0][(int)player_pos_.z - 3] = 2;
    //                map_[(int)player_pos_.x][0][(int)player_pos_.z - 4] = 2;
    //                time_ = 0;
    //                count_--;
    //                SetCloudPos(player_pos_.x, player_pos_.y + 1, player_pos_.z - 2);
    //                Cloud();
    //            }
    //        }
    //    }
    //}

    //ビューポート行列
    float w = (FLOAT)Direct3D::screenWidth_ / 2.0f;

    float h = (FLOAT)Direct3D::screenHeight_ / 2.0f;

    XMMATRIX vp = {
        w,  0, 0, 0,
        0, -h, 0, 0,
        0,  0, 1, 0,
        w,  h, 0, 1
    };

    //各行列の逆行列
    XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
    XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());
    XMMATRIX invPrj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());

    //マウス位置（手前）
    XMFLOAT3 mousePosFront = Input::GetMousePosition();
    mousePosFront.z = 0.0f;

    //マウス位置（奥）
    XMFLOAT3 mousePosBack = Input::GetMousePosition();
    mousePosBack.z = 1.0f;

    //逆行列の合成
    XMMATRIX invTransform = invVP * invPrj * invView;

    XMVECTOR vStart = XMVector3TransformCoord(XMLoadFloat3(&mousePosFront), invTransform);
    XMVECTOR vTarget = XMVector3TransformCoord(XMLoadFloat3(&mousePosBack), invTransform);

    int bufX, bufY, bufZ = 0;
    float minDistance = 9999999;
    bool IsHit = false;

    if (Input::IsMouseButtonDown(0))
    {
        for (int x = 0; x < STAGE_SIZE_X; x++)
        {
            for (int z = 0; z < STAGE_SIZE_Z; z++)
            {
                for (int y = 0; y < stage_[x][z].height; y++)
                {
                    RayCastData ray;

                    XMStoreFloat3(&ray.start, vStart);
                    XMStoreFloat3(&ray.dir, vTarget - vStart);

                    int type = stage_[x][z].type;
                    Transform trans;
                    trans.position_.x = x;
                    trans.position_.y = y;
                    trans.position_.z = z;
                    Model::SetTransform(hModel_[stage_[x][z].type], trans);
                    Model::RayCast(hModel_[stage_[x][z].type], &ray);

                    if (ray.hit)
                    {
                        IsHit = true;
                        if (minDistance > ray.dist)
                        {
                            minDistance = ray.dist;
                            bufX = x;
                            bufY = y;
                            bufZ = z;
                        }
                    }
                }
            }
        }

        //マウスの位置にブロックがあったら
        if (IsHit)
        {
            //クリックしたところが何もなかったら
            if (stage_[bufX][bufZ].type == empty)
            {
                //if (stage_[bufX][bufZ].type == log)
                //{
                //    stage_[bufX][bufZ].type = log;
                //    stage_[bufX][bufZ - 1].type = coin;
                //    stage_[bufX][bufZ - 2].type = coin;
                //}
                if (stage_[bufX][bufZ - 1].type == log)
                {
                    stage_[bufX][bufZ].type = coin;
                    stage_[bufX][bufZ + 1].type = coin;
                    stage_[bufX][bufZ + 2].type = coin;
                }
                else if (stage_[bufX][bufZ - 2].type == log)
                {
                    stage_[bufX][bufZ - 1].type = coin;
                    stage_[bufX][bufZ].type = coin;
                    stage_[bufX][bufZ + 1].type = coin;
                }
                else if (stage_[bufX][bufZ - 3].type == log)
                {
                    stage_[bufX][bufZ].type = coin;
                    stage_[bufX][bufZ - 1].type = coin;
                    stage_[bufX][bufZ - 2].type = coin;
                }
                //if (stage_[bufX][bufZ].type == log)
                //{
                //    stage_[bufX][bufZ].type = coin;
                //    stage_[bufX][bufZ + 1].type = coin;
                //    stage_[bufX][bufZ + 2].type = coin;
                //}
                //if (stage_[bufX][bufZ + 1].type == log)
                //{
                //    stage_[bufX][bufZ].type = coin;
                //    stage_[bufX][bufZ - 1].type = coin;
                //    stage_[bufX][bufZ - 2].type = coin;
                //}
                //else if (stage_[bufX][bufZ + 2].type == log)
                //{
                //    stage_[bufX][bufZ - 1].type = coin;
                //    stage_[bufX][bufZ].type = coin;
                //    stage_[bufX][bufZ + 1].type = coin;
                //}

                //stage_[bufX][bufZ - 1].type = coin;
                //stage_[bufX][bufZ].type = coin;
                //stage_[bufX][bufZ + 1].type = coin;
            }
        }
    }
}

//描画
void Stage::Draw()
{
    for (int x = 0; x < STAGE_SIZE_X; x++)
    {
            for (int z = 0; z < STAGE_SIZE_Z; z++)
            {
                for (int y = 0; y < stage_[x][z].height; y++)
                {
                    int type = stage_[x][z].type;
                    transform_.position_ = XMFLOAT3(x, 0, z + 1);
                    transform_.rotate_ = XMFLOAT3(0, 0, 0);
                    transform_.scale_ = XMFLOAT3(1, 1, 1);

                    switch (stage_[x][z].type)
                    {
                    case empty:
                        break;
                    case log:
                        transform_.rotate_.y = 90;
                        Model::SetTransform(hModel_[type], transform_);
                        Model::Draw(hModel_[type]);
                        break;
                    case coin:
                        transform_.position_ = XMFLOAT3(x + 0.25, 0.5, z + 1);
                        transform_.scale_ = XMFLOAT3(0.5, 1, 2);
                        Model::SetTransform(hModel_[type], transform_);
                        Model::Draw(hModel_[type]);
                        break;
                    case enemy:
                        transform_.rotate_.y = 90;
                        Model::SetTransform(hModel_[type], transform_);
                        Model::Draw(hModel_[type]);
                        break;
                    case player:
                        transform_.rotate_.y = 90;
                        Model::SetTransform(hModel_[type], transform_);
                        Model::Draw(hModel_[type]);
                        break;
                    }
                }
        }
    }

    //pText->Draw(100, 200, "count");
    //pText->Draw(200, 200, count_);
}

//開放
void Stage::Release()
{
}

////そこは壁か
bool Stage::IsWall(int x,  int z)
{
    return (stage_[x][z].type == 1);
}

bool Stage::IsWallX(int x,  int z)
{
    return (stage_[x][z].type == 2);
}

bool Stage::IsWallM(int x,  int z)
{
    return (stage_[x][z].type == 2);
}

//bool Stage::IsWallM(int x, int y)
//{
//    return (map_[x][y] == 10);
//}
//
bool Stage::IsPipe(int x,  int z)
{
    return (stage_[x][z].type == 2);
}

bool Stage::IsEmpty(int x,  int z)
{
    return (stage_[x][z].type == 0);
}