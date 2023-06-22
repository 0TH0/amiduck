#include "Stage.h"
#include "Player.h"
#include "Scene/PlayScene.h"

#include "Player.h"
#include "Star.h"
#include "ItemBox.h"
#include "Item.h"

#include "Engine/SceneManager.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"
#include "Engine/Input.h"
#include "Engine/SphereCollider.h"
#include "Engine/BoxCollider.h"
#include "Engine/Camera.h"
#include "Engine/Audio.h"
#include "Fire.h"
#include "EnemyRed.h"
#include "EnemyBlue.h"
#include "EnemyGreen.h"
#include "Manager/StageAudio.h"
#include "Manager/StageEffect.h"

namespace
{
    static Item* pItem;
    static Fire* pFire;
    static int bufX, bufY, bufZ;
    static XMINT3 buf[5];
    static bool IsHit = false;
    static float minDistance;
    static XMVECTOR vStart;
    static XMVECTOR vTarget;
    static Transform trans;
    static int bridgeMax = 5;
}

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), woodCoolTime_(300),time_(0),stage_(),
    bridgeCount_(0),enemyPos_(),hAudio_(-1),hModel_(),player_pos_(),stagePos_(), ShouldPoPRandStage_(true),
    GuidePopBridgePos(),pPlayer_()
{
}

//デストラクタ
Stage::~Stage()
{
}

void Stage::StageLoad()
{
    //Csv読み込み
    csv = new CsvReader();
    csv->Load("Csv\\stage.csv");

    //判定
    hModel_[EMPTY] = Model::Load("DebugCollision\\BoxCollider.fbx");
    assert(hModel_[EMPTY] >= 0);

    //ブロック
    hModel_[LOG] = Model::Load("Stage\\log.fbx");
    assert(hModel_[LOG] >= 0);

    //旗先端
    hModel_[BRIDGE] = Model::Load("Stage\\wood_board.fbx");
    assert(hModel_[BRIDGE] >= 0);

    hModel_[BRIDGE_FADE] = Model::Load("Stage\\wood_board.fbx");
    assert(hModel_[BRIDGE_FADE] >= 0);

    hModel_[PLAYER] = Model::Load("Stage\\log.fbx");
    assert(hModel_[PLAYER] >= 0);

    hModel_[STAR] = Model::Load("Stage\\log.fbx");
    assert(hModel_[STAR] >= 0);

    hModel_[ITEMBOX] = Model::Load("Stage\\log.fbx");
    assert(hModel_[ITEMBOX] >= 0);

    hModel_[FIRE] = Model::Load("Model\\fire.fbx");
    assert(hModel_[FIRE] >= 0);

    hModel_[FIRE_RIGHT] = Model::Load("Model\\fire.fbx");
    assert(hModel_[FIRE_RIGHT] >= 0);
}

//初期化
void Stage::Initialize()
{
    Instantiate<Item>(this);
    for (int x = 0; x < STAGE_SIZE_X; x++)
    {
        for (int z = 0; z < STAGE_SIZE_Z; z++)
        {
            stage_[x][z].height = 1;
            stage_[x][z].type = 0;
        }
    }

    //オーディオ初期化
    StageAudio::Initialize();
    StageLoad();

    for (int x = 0; x < STAGE_SIZE_X; x++)
    {
        for (int z = 0; z < STAGE_SIZE_Z; z++)
        {
            stage_[x][z].type = csv->GetValue(x, z);
        }
    }

    //ランダムなステージを出すか
    if (ShouldPoPRandStage_) RandStage();

    for (int x = 0; x < STAGE_SIZE_X; x++)
    {
        for (int z = 0; z < STAGE_SIZE_Z; z++)
        {
            //プレイヤー登場
            if (stage_[x][z].type == PLAYER)
            {
                Player* pPlayer = Instantiate<Player>(GetParent());
                pPlayer->SetPosition(x, 0, z);
            }
            if (stage_[x][z].type == STAR)
            {
                Star* pStar = Instantiate<Star>(GetParent());
                pStar->SetPosition(x, 1.25f, z);

            }
            if (stage_[x][z].type == ITEMBOX)
            {
                ItemBox* pItemBox = Instantiate<ItemBox>(GetParent());
                pItemBox->SetPosition(x, 1.25f, z);
            }
            if (stage_[x][z].type == FIRE)
            {
                pFire = Instantiate<Fire>(GetParent());
                pFire->SetPosition(x, 1.25f, z);
            }
            if (stage_[x][z].type == FIRE_RIGHT)
            {
                pFire = Instantiate<Fire>(GetParent());
                pFire->SetPosition(x, 1.25f, z);
                pFire->SetRight(true);
            }
            if (stage_[x][z].type == ENEMY_RED)
            {
                EnemyRed* pEnemyRed = Instantiate<EnemyRed>(GetParent());
                pEnemyRed->SetPosition(x, 1.5f, z);
            }
            if (stage_[x][z].type == ENEMY_BLUE)
            {
                EnemyBlue* pEnemyBlue = Instantiate<EnemyBlue>(GetParent());
                pEnemyBlue->SetPosition(x, 1.5f, z);
            }
            if (stage_[x][z].type == ENEMY_GREEN)
            {
                EnemyGreen* pEnemyGreen = Instantiate<EnemyGreen>(GetParent());
                pEnemyGreen->SetPosition(x, 1.5f, z);
            }
        }
    }

    pText->Initialize();
    //
    pItem = (Item*)FindObject("Item");
}

//更新
void Stage::Update()
{
    pPlayer_ = (Player*)FindObject("Player");
    
    if (!pPlayer_->GetReturn()) player_pos_.x = pPlayer_->GetPosition().x + 1;
    else player_pos_.x = pPlayer_->GetPosition().x - 1;

    player_pos_.z = pPlayer_->GetPosition().z;

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

    vStart = XMVector3TransformCoord(XMLoadFloat3(&mousePosFront), invTransform);
    vTarget = XMVector3TransformCoord(XMLoadFloat3(&mousePosBack), invTransform);

    bufX, bufY, bufZ = 0;
    minDistance = 9999999.f;
    IsHit = false;

    PopBridge();
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
                stagePos_ = XMFLOAT3((float)x, (float)y, (float)z);
                int type = stage_[x][z].type;
                transform_.position_ = XMFLOAT3(stagePos_.x, 0, stagePos_.z);
                transform_.rotate_ = XMFLOAT3(0, 0, 0);
                transform_.scale_ = XMFLOAT3(1, 1, 1);
                Direct3D::SetBlendMode(Direct3D::BLEND_DEFAULT);
                Direct3D::SetShader(Direct3D::SHADER_3D);

                switch (stage_[x][z].type)
                {
                case EMPTY:
                    Model::SetTransform(hModel_[type], transform_);
                    //Model::Draw(hModel_[type]);
                    break;
                case LOG:
                    transform_.rotate_ = XMFLOAT3(90, 90, 0);
                    Direct3D::SetShader(Direct3D::SHADER_NORMALMAP);
                    Model::SetTransform(hModel_[type], transform_);
                    Model::Draw(hModel_[type]);
                    break;
                case BRIDGE:
                    transform_.position_ = XMFLOAT3(x, 0.5 + y, z);
                    transform_.scale_ = XMFLOAT3(0.5, 1, 2);
                    Model::SetTransform(hModel_[type], transform_);
                    Model::Draw(hModel_[type]);
                    break;
                case BRIDGE_FADE:
                    transform_.position_ = XMFLOAT3(x + 0.25, 0.5 + y, z);
                    transform_.scale_ = XMFLOAT3(0.5, 1, 2);
                    Model::SetTransform(hModel_[type], transform_);
                    Model::Draw(hModel_[type], 0.5);
                    break;
                //何もしない
                case FIRE:
                case FIRE_RIGHT:
                case CORNER:
                    break;

                default:
                    transform_.rotate_ = XMFLOAT3(90, 90, 0);
                    Model::SetTransform(hModel_[LOG], transform_);
                    Model::Draw(hModel_[LOG]);
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

//橋を出現させる
void Stage::PopBridge()
{
    //マウスを左クリックして、橋の残りの数が0より多いとき
    if (Input::IsMouseButtonDown(0) && pItem->GetwoodCount() > 0)
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
            if (stage_[bufX][bufZ].type == EMPTY)
            {
                if (stage_[bufX][bufZ - 1].type == LOG)
                {
                    stage_[bufX][bufZ].type = BRIDGE;
                    stage_[bufX][bufZ + 1].type = BRIDGE;
                    stage_[bufX][bufZ + 2].type = BRIDGE;
                    stage_[bufX][bufZ + 3].type = BRIDGE;
                    stage_[bufX][bufZ + 4].type = BRIDGE;
                    effectPos_.x = bufX;
                    effectPos_.z = bufZ + 3;
                    StageEffect::PopBridgeEffect(effectPos_);
                    StageAudio::PopStageAudio();
                    pItem->MinWoodCount();
                }
                else if (stage_[bufX][bufZ - 2].type == LOG)
                {
                    stage_[bufX][bufZ - 1].type = BRIDGE;
                    stage_[bufX][bufZ].type = BRIDGE;
                    stage_[bufX][bufZ + 1].type = BRIDGE;
                    stage_[bufX][bufZ + 2].type = BRIDGE;
                    stage_[bufX][bufZ + 3].type = BRIDGE;
                    effectPos_.x = bufX;
                    effectPos_.z = bufZ + 2;
                    StageEffect::PopBridgeEffect(effectPos_);
                    StageAudio::PopStageAudio();
                    pItem->MinWoodCount();
                }
                else if (stage_[bufX][bufZ - 3].type == LOG)
                {
                    stage_[bufX][bufZ + 2].type = BRIDGE;
                    stage_[bufX][bufZ + 1].type = BRIDGE;
                    stage_[bufX][bufZ].type = BRIDGE;
                    stage_[bufX][bufZ - 1].type = BRIDGE;
                    stage_[bufX][bufZ - 2].type = BRIDGE;
                    effectPos_.x = bufX;
                    effectPos_.z = bufZ + 1;
                    StageEffect::PopBridgeEffect(effectPos_);
                    StageAudio::PopStageAudio();
                    pItem->MinWoodCount();
                }
                else if (stage_[bufX][bufZ - 4].type == LOG)
                {
                    stage_[bufX][bufZ + 1].type = BRIDGE;
                    stage_[bufX][bufZ].type = BRIDGE;
                    stage_[bufX][bufZ - 1].type = BRIDGE;
                    stage_[bufX][bufZ].type = BRIDGE;
                    stage_[bufX][bufZ - 3].type = BRIDGE;
                    effectPos_.x = bufX;
                    effectPos_.z = bufZ;
                    StageEffect::PopBridgeEffect(effectPos_);
                    StageAudio::PopStageAudio();
                    pItem->MinWoodCount();
                }
                else if (stage_[bufX][bufZ - 5].type == LOG)
                {
                    stage_[bufX][bufZ].type = BRIDGE;
                    stage_[bufX][bufZ - 1].type = BRIDGE;
                    stage_[bufX][bufZ - 2].type = BRIDGE;
                    stage_[bufX][bufZ - 1].type = BRIDGE;
                    stage_[bufX][bufZ - 4].type = BRIDGE;
                    effectPos_.x = bufX;
                    effectPos_.z = bufZ - 1;
                    StageEffect::PopBridgeEffect(effectPos_);
                    StageAudio::PopStageAudio();
                    pItem->MinWoodCount();
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            stage_[buf[i].x][buf[i].z].type = EMPTY;
        }

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
            if (stage_[bufX][bufZ].type == EMPTY)
            {

                if (stage_[bufX][bufZ - 1].type == LOG)
                {
                    stage_[bufX][bufZ].type = BRIDGE_FADE;
                    stage_[bufX][bufZ + 1].type = BRIDGE_FADE;
                    stage_[bufX][bufZ + 2].type = BRIDGE_FADE;
                    stage_[bufX][bufZ + 3].type = BRIDGE_FADE;
                    stage_[bufX][bufZ + 4].type = BRIDGE_FADE;

                    buf[0] = XMINT3(bufX, 1, bufZ);
                    buf[1] = XMINT3(bufX, 1, bufZ + 1);
                    buf[2] = XMINT3(bufX, 1, bufZ + 2);
                    buf[3] = XMINT3(bufX, 1, bufZ + 3);
                    buf[4] = XMINT3(bufX, 1, bufZ + 4);
                }
                else if (stage_[bufX][bufZ - 2].type == LOG)
                {
                    stage_[bufX][bufZ - 1].type = BRIDGE_FADE;
                    stage_[bufX][bufZ].type = BRIDGE_FADE;
                    stage_[bufX][bufZ + 1].type = BRIDGE_FADE;
                    stage_[bufX][bufZ + 2].type = BRIDGE_FADE;
                    stage_[bufX][bufZ + 3].type = BRIDGE_FADE;

                    buf[0] = XMINT3(bufX, 1, bufZ - 1);
                    buf[1] = XMINT3(bufX, 1, bufZ);
                    buf[2] = XMINT3(bufX, 1, bufZ + 1);
                    buf[3] = XMINT3(bufX, 1, bufZ + 2);
                    buf[4] = XMINT3(bufX, 1, bufZ + 3);
                }
                else if (stage_[bufX][bufZ - 3].type == LOG)
                {
                    stage_[bufX][bufZ + 2].type = BRIDGE_FADE;
                    stage_[bufX][bufZ + 1].type = BRIDGE_FADE;
                    stage_[bufX][bufZ].type = BRIDGE_FADE;
                    stage_[bufX][bufZ - 1].type = BRIDGE_FADE;
                    stage_[bufX][bufZ - 2].type = BRIDGE_FADE;

                    buf[0] = XMINT3(bufX, 1, bufZ + 2);
                    buf[1] = XMINT3(bufX, 1, bufZ + 1);
                    buf[2] = XMINT3(bufX, 1, bufZ);
                    buf[3] = XMINT3(bufX, 1, bufZ - 1);
                    buf[4] = XMINT3(bufX, 1, bufZ - 2);
                }
                else if (stage_[bufX][bufZ - 4].type == LOG)
                {
                    stage_[bufX][bufZ + 1].type = BRIDGE_FADE;
                    stage_[bufX][bufZ].type = BRIDGE_FADE;
                    stage_[bufX][bufZ - 1].type = BRIDGE_FADE;
                    stage_[bufX][bufZ].type = BRIDGE_FADE;
                    stage_[bufX][bufZ - 3].type = BRIDGE_FADE;

                    buf[0] = XMINT3(bufX, 1, bufZ + 1);
                    buf[1] = XMINT3(bufX, 1, bufZ);
                    buf[2] = XMINT3(bufX, 1, bufZ - 1);
                    buf[3] = XMINT3(bufX, 1, bufZ);
                    buf[4] = XMINT3(bufX, 1, bufZ - 3);
                }
                else if (stage_[bufX][bufZ - 5].type == LOG)
                {
                    stage_[bufX][bufZ].type = BRIDGE_FADE;
                    stage_[bufX][bufZ - 1].type = BRIDGE_FADE;
                    stage_[bufX][bufZ - 2].type = BRIDGE_FADE;
                    stage_[bufX][bufZ - 1].type = BRIDGE_FADE;
                    stage_[bufX][bufZ - 4].type = BRIDGE_FADE;

                    buf[0] = XMINT3(bufX, 1, bufZ);
                    buf[1] = XMINT3(bufX, 1, bufZ - 1);
                    buf[2] = XMINT3(bufX, 1, bufZ - 2);
                    buf[3] = XMINT3(bufX, 1, bufZ - 1);
                    buf[4] = XMINT3(bufX, 1, bufZ - 4);
                }
            }
        }
    }
}

void Stage::RandStage()
{
    //マップの自動生成
    while(bridgeCount_ < 15)
    {
        int randX = (rand() % STAGE_SIZE_X - 1);
        int randZ = (rand() % STAGE_SIZE_Z - 1);

        if (randX == STAGE_SIZE_X || randX == 0)
        {
            continue;
        }

        if (randZ == 28 || randZ == 22 || randZ == 16 || randZ == 10)
        {
            stage_[randX][randZ + 1].type = BRIDGE;
            stage_[randX][randZ].type     = BRIDGE;
            stage_[randX][randZ - 1].type = BRIDGE;
            stage_[randX][randZ - 2].type = BRIDGE;
            stage_[randX][randZ - 3].type = BRIDGE;
            bridgeCount_++;
        }
        else
        {
            randX = rand() % STAGE_SIZE_X - 5;
            randZ = (rand() % (STAGE_SIZE_Z - 5) + 5);
        }
    }

    //アイテムボックス出現
    //{
    //    int count = 0;
    //    while (count < 10)
    //    {
    //        int randX = (rand() % STAGE_SIZE_X - 1);
    //        int randZ = (rand() % STAGE_SIZE_Z - 1);

    //        if (randZ == 34 || randZ == 28 || randZ == 22 || randZ == 16 || randZ == 10 || randZ == 4)
    //        {
    //            stage_[randX][randZ + 2].type = ITEMBOX;
    //            count++;
    //        }
    //        else
    //        {
    //            randX = (rand() % STAGE_SIZE_X - 1);
    //            randZ = (rand() % STAGE_SIZE_Z - 1);
    //        }
    //    }
    //}

    //{
    //    int count = 0;
    //    while (count < 5)
    //    {
    //        int randX = (rand() % STAGE_SIZE_X - 1);
    //        int randZ = (rand() % STAGE_SIZE_Z - 1);

    //        if (randZ == 34 || randZ == 28 || randZ == 22 || randZ == 16 || randZ == 10 || randZ == 4)
    //        {
    //            stage_[randX][randZ + 2].type = STAR;
    //            count++;
    //        }
    //        else
    //        {
    //            randX = (rand() % STAGE_SIZE_X - 1);
    //            randZ = (rand() % STAGE_SIZE_Z - 1);
    //        }
    //    }
    //}
}

bool Stage::IsBridge(int x,  int z)
{
    return (stage_[x][z].type == BRIDGE);
}

bool Stage::IsCorner(int x,  int z)
{
    return (stage_[x][z].type == CORNER);
}