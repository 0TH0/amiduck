#include "Stage.h"
#include "Player.h"
#include "PlayScene.h"
#include "Enemy.h"
#include "Player.h"
#include "Coin.h"
#include "Star.h"
#include "ItemBox.h"
#include "ItemUI.h"

#include "Engine/SceneManager.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"
#include "Engine/Input.h"
#include "Engine/SphereCollider.h"
#include "Engine/BoxCollider.h"
#include "Engine/Camera.h"
#include "Engine/Audio.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), woodCoolTime_(300),time_(0),stage_(),pParticle_(nullptr),
    bridgeCount_(0),enemyPos_(),hAudio_(-1),hModel_(),player_pos_(),stagePos_()
{
}

//デストラクタ
Stage::~Stage()
{
}

void Stage::StageLoad()
{
    //Csv読み込み
    csv.Load("Csv\\map3.csv");

    //空箱
    //hModel_[-1] = Model::Load("-1.fbx");
    //assert(hModel_[0] >= 0);

    //ブロック
    hModel_[log] = Model::Load("Stage\\log.fbx");
    assert(hModel_[log] >= 0);

    //旗先端
    hModel_[coin] = Model::Load("Stage\\wood_board.fbx");
    assert(hModel_[coin] >= 0);

    hModel_[bridge] = Model::Load("Stage\\wood_board.fbx");
    assert(hModel_[bridge] >= 0);

    hModel_[enemy] = Model::Load("Stage\\log.fbx");
    assert(hModel_[enemy] >= 0);

    hModel_[player] = Model::Load("Stage\\log.fbx");
    assert(hModel_[player] >= 0);

    hModel_[star] = Model::Load("Stage\\log.fbx");
    assert(hModel_[star] >= 0);

    hModel_[itembox] = Model::Load("Stage\\log.fbx");
    assert(hModel_[itembox] >= 0);
    
    //煙の音
    hAudio_ = Audio::Load("Audio\\smoke.wav", 5);
    assert(hAudio_ >= 0);
}

void Stage::Cloud()
{
    data.textureFileName = "Particle\\Cloud.png";
    data.positionErr = XMFLOAT3(0.1f, 0, 0.1f);
    data.delay = 0;
    data.number = 5;
    data.lifeTime = 60;
    data.dir = XMFLOAT3(0, 1, 0);
    data.dirErr = XMFLOAT3(0, 0, 0);
    data.speed = 0.01f;
    data.speedErr = 0.5;
    data.size = XMFLOAT2(2, 2);
    data.sizeErr = XMFLOAT2(0.4f, 0.4f);
    data.scale = XMFLOAT2(1.03f, 1.02f);
    float color = 0.5;
    data.color = XMFLOAT4(color, color, color, 0.1f);
    pParticle_->Start(data);

    Audio::Play(hAudio_);
}

//初期化
void Stage::Initialize()
{
    Instantiate<ItemUI>(this);
    for (int x = 0; x < STAGE_SIZE_X; x++)
    {
        for (int z = 0; z < STAGE_SIZE_Z; z++)
        {
            stage_[x][z].height = 1;
            stage_[x][z].type = 0;
        }
    }

    StageLoad();

    for (int x = 0; x < STAGE_SIZE_X; x++)
    {
        for (int z = 0; z < STAGE_SIZE_Z; z++)
        {
            stage_[x][z].type = csv.GetValue(x, -z + 38);
        }
    }

    //あとで関数作る
    //マップの自動生成
    while(bridgeCount_ < 15)
    {
        int randX = (rand() % (STAGE_SIZE_X - 5) + 5);
        int randZ = (rand() % (STAGE_SIZE_Z - 5) + 5);

        if (randZ == 29 || randZ == 23 || randZ == 17 || randZ == 11)
        {
            stage_[randX][randZ + 1].type = coin;
            stage_[randX][randZ].type     = coin;
            stage_[randX][randZ - 1].type = coin;
            stage_[randX][randZ - 2].type = coin;
            stage_[randX][randZ - 3].type = coin;
            bridgeCount_++;
        }
    }

    //アイテムボックス出現
    {
        int count = 0;
        while (count < 10)
        {
            int randX = (rand() % STAGE_SIZE_X - 1);
            int randZ = (rand() % STAGE_SIZE_Z - 1);

            if (randZ == 29 || randZ == 23 || randZ == 17 || randZ == 11)
            {
                stage_[randX][randZ + 2].type = itembox;
                count++;
            }
        }
    }

    {
        int count = 0;
        while (count < 5)
        {
            int randX = (rand() % STAGE_SIZE_X - 1);
            int randZ = (rand() % STAGE_SIZE_Z - 1);

            if (randZ == 29 || randZ == 23 || randZ == 17 || randZ == 11)
            {
                stage_[randX][randZ + 2].type = star;
                count++;
            }
        }
    }


    //読み込んだモデルの初期化
    for (int x = 0; x < STAGE_SIZE_X; x++)
    {
        for (int z = 0; z < STAGE_SIZE_Z; z++)
        {
            if (stage_[x][z].type == -1)
            {
                //-1* p-1 = Instantiate<-1>(this);
            }

            //コイン登場
            if (stage_[x][z].type == coin)
            {
                Coin* pCoin = Instantiate<Coin>(GetParent());
                pCoin->SetPosition(x + 0.25f, 1, z + 1.f);
            }

            //エネミー登場
            if (stage_[x][z].type == enemy)
            {
                Enemy* pEnemy = Instantiate<Enemy>(GetParent());
                pEnemy->SetPosition((float)x, 1, z + 1.f);
            }

            //プレイヤー登場
            if (stage_[x][z].type == player)
            {
                Player* pPlayer = Instantiate<Player>(GetParent());
                pPlayer->SetPosition((float)x, 0, z + 1.f);
            }
            if (stage_[x][z].type == star)
            {
                Star* pStar = Instantiate<Star>(GetParent());
                pStar->SetPosition((float)x, 1.25f, z + 1.f);

            }
            if (stage_[x][z].type == itembox)
            {
                ItemBox* pItemBox = Instantiate<ItemBox>(GetParent());
                pItemBox->SetPosition((float)x, 1.25f, z + 1.f);
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
    Enemy* pEnemy = (Enemy*)FindObject("Enemy");

    if (!pPlayer->GetReturn()) player_pos_.x = pPlayer->GetPosition().x + 1;
    else player_pos_.x = pPlayer->GetPosition().x - 1;

    player_pos_.z = pPlayer->GetPosition().z;

    enemyPos_ = pEnemy->GetPosition();

    //ビューポート行列
    float w = Camera::GetScrWDiv2();

    float h = Camera::GetScrHDiv2();

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

    if (Input::IsMouseButtonDown(0) && woodCoolTime_ >= 300)
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
                    trans.position_.x = (float)x;
                    trans.position_.y = (float)y;
                    trans.position_.z = (float)z;
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
            if (stage_[bufX][bufZ].type == -1)
            {
                if (stage_[bufX][bufZ - 1].type == log)
                {
                    stage_[bufX][bufZ].type = coin;
                    stage_[bufX][bufZ + 1].type = coin;
                    stage_[bufX][bufZ + 2].type = coin;
                    stage_[bufX][bufZ + 3].type = coin;
                    stage_[bufX][bufZ + 4].type = coin;
                    data.position.x = bufX;
                    data.position.z = bufZ + 2;
                    Cloud();
                    woodCoolTime_ = 0;
                }
                else if (stage_[bufX][bufZ - 2].type == log)
                {
                    stage_[bufX][bufZ - 1].type = coin;
                    stage_[bufX][bufZ].type = coin;
                    stage_[bufX][bufZ + 1].type = coin;
                    stage_[bufX][bufZ + 2].type = coin;
                    stage_[bufX][bufZ + 3].type = coin;
                    data.position.x = bufX;
                    data.position.z = bufZ + 1;
                    Cloud();
                    woodCoolTime_ = 0;
                }
                else if (stage_[bufX][bufZ - 3].type == log)
                {
                    stage_[bufX][bufZ + 2].type = coin;
                    stage_[bufX][bufZ + 1].type = coin;
                    stage_[bufX][bufZ].type =     coin;
                    stage_[bufX][bufZ - 1].type = coin;
                    stage_[bufX][bufZ - 2].type = coin;
                    data.position.x = bufX;
                    data.position.z = bufZ;
                    Cloud();
                    woodCoolTime_ = 0;
                }
                else if (stage_[bufX][bufZ + 3].type == log)
                {
                    stage_[bufX][bufZ].type = coin;
                    stage_[bufX][bufZ + 1].type = coin;
                    stage_[bufX][bufZ + 2].type = coin;
                    woodCoolTime_ = 0;
                }
            }
        }
    }

    //卵のAI予定
    if(Input::IsKeyDown(DIK_J))
    {
        stage_[(int)enemyPos_.x][(int)enemyPos_.z + 1].type = coin;
        stage_[(int)enemyPos_.x][(int)enemyPos_.z + 2].type = coin;
        stage_[(int)enemyPos_.x][(int)enemyPos_.z + 3].type = coin;
    }

    if (woodCoolTime_ >= 300)
    {
        woodCoolTime_ = 300;
    }
    else
    {
        woodCoolTime_++;
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
                    stagePos_ = XMFLOAT3((float)x,(float)y, (float)z);
                    int type = stage_[x][z].type;
                    transform_.position_ = XMFLOAT3(stagePos_.x, 0, stagePos_.z + 1);
                    transform_.rotate_ = XMFLOAT3(0, 0, 0);
                    transform_.scale_ = XMFLOAT3(1, 1, 1);
                    Direct3D::SetBlendMode(Direct3D::BLEND_DEFAULT);
                    Direct3D::SetShader(Direct3D::SHADER_3D);

                    switch (stage_[x][z].type)
                    {
                    case -1:
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
                    case bridge:
                        transform_.position_ = XMFLOAT3(x + 0.25, 0.5, z + 1);
                        transform_.scale_ = XMFLOAT3(0.5, 1, 2);
                        Model::SetTransform(hModel_[type], transform_);
                        Model::Draw(hModel_[type], 0.3);
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
                    case star:
                        transform_.rotate_.y = 90;
                        Model::SetTransform(hModel_[type], transform_);
                        Model::Draw(hModel_[type]);
                        break;
                    case itembox:
                        transform_.rotate_.y = 90;
                        Model::SetTransform(hModel_[type], transform_);
                        Model::Draw(hModel_[type]);
                        break;
                    }
                }
        }
    }
}

//開放
void Stage::Release()
{
}

//そこは壁か
bool Stage::IsWall(int x,  int z)
{
    return (stage_[x][z].type == 1);
}

bool Stage::IsBridge(int x,  int z)
{
    return (stage_[x][z].type == 2);
}

bool Stage::IsEmpty(int x,  int z)
{
    return (stage_[x][z].type == 0);
}