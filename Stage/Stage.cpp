#include "Stage.h"
#include "../Player.h"
#include "../Scene/PlayScene.h"
#include "../Player.h"
#include "../Item/ItemBox.h"
#include "../Item/Item.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Model.h"
#include "../Engine/CsvReader.h"
#include "../Engine/Input.h"
#include "../Engine/SphereCollider.h"
#include "../Engine/BoxCollider.h"
#include "../Engine/Camera.h"
#include "../Engine/Audio.h"
#include "../Enemy/EnemyRed.h"
#include "../Enemy/EnemyBlue.h"
#include "../Enemy/EnemyGreen.h"
#include "../Manager/StageAudio.h"
#include "../Manager/StageEffect.h"
#include "../Engine/VFX.h"

namespace
{
    static Item* pItem;
    static int bufX, bufY, bufZ;
    static XMINT3 buf[5];
    static bool IsHit = false;
    static float minDistance;
    static XMVECTOR vStart;
    static XMVECTOR vTarget;
    static Transform trans;
    static const int MAX_BRIDGE = 5;
    static const int MAX_RAND_BRIDGE = 15;
}

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), woodCoolTime_(300),stage_(),
    bridgeCount_(0),enemyPos_(),hAudio_(-1),hModel_(),player_pos_(),stagePos_(), ShouldPopRandStage_(true),
    GuidePopBridgePos(),pPlayer_(), bridgeRimit_(7),csv(),effectPos_()
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
    assert(hModel_[EMPTY] >= ZERO);

    //ブロック
    hModel_[LOG] = Model::Load("Stage\\log.fbx");
    assert(hModel_[LOG] >= ZERO);

    //旗先端
    hModel_[BRIDGE] = Model::Load("Stage\\wood_board.fbx");
    assert(hModel_[BRIDGE] >= ZERO);

    //ガイドの橋
    hModel_[BRIDGE_FADE] = Model::Load("Stage\\wood_board.fbx");
    assert(hModel_[BRIDGE_FADE] >= ZERO);
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
    if (ShouldPopRandStage_) RandStage();

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
            if (stage_[x][z].type == ITEMBOX)
            {
                ItemBox* pItemBox = Instantiate<ItemBox>(GetParent());
                pItemBox->SetPosition(x, 1.25f, z);
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
    pItem = (Item*)FindObject("Item");
}

//更新
void Stage::Update()
{
    //各行列の逆行列
    XMMATRIX invVP = XMMatrixInverse(nullptr, Camera::GetViewPortMatrix());
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

    bufX, bufY, bufZ = ZERO;
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
                transform_.position_ = XMFLOAT3(stagePos_.x, y, stagePos_.z);
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
                    transform_.scale_ = XMFLOAT3(0.25, 1, 3);
                    Model::SetTransform(hModel_[type], transform_);
                    Model::Draw(hModel_[type]);
                    break;
                case BRIDGE_FADE:
                    transform_.position_ = XMFLOAT3(x, 0.5 + y, z);
                    transform_.scale_ = XMFLOAT3(0.25, 1, 3);
                    Model::SetTransform(hModel_[type], transform_);
                    Model::Draw(hModel_[type], 0.5);
                    break;
                //何もしない
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
    if (Input::IsMouseButtonDown(Input::LEFT) && pItem->GetwoodCount() > ZERO)
    {
        //bridgeRimit_で橋の端をクリックできなくする
        for (int x = bridgeRimit_; x < STAGE_SIZE_X - bridgeRimit_; x++)
        {
            for (int z = ZERO; z < STAGE_SIZE_Z; z++)
            {
                for (int y = ZERO; y < stage_[x][z].height; y++)
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
                    PopBridgeEffect();
                    pItem->MinWoodCount();
                }
                else if (stage_[bufX][bufZ - 2].type == LOG)
                {
                    stage_[bufX][bufZ - 1].type = BRIDGE;
                    stage_[bufX][bufZ].type = BRIDGE;
                    stage_[bufX][bufZ + 1].type = BRIDGE;
                    stage_[bufX][bufZ + 2].type = BRIDGE;
                    stage_[bufX][bufZ + 3].type = BRIDGE;
                    PopBridgeEffect();
                    pItem->MinWoodCount();
                }
                else if (stage_[bufX][bufZ - 3].type == LOG)
                {
                    stage_[bufX][bufZ + 2].type = BRIDGE;
                    stage_[bufX][bufZ + 1].type = BRIDGE;
                    stage_[bufX][bufZ].type = BRIDGE;
                    stage_[bufX][bufZ - 1].type = BRIDGE;
                    stage_[bufX][bufZ - 2].type = BRIDGE;
                    PopBridgeEffect();
                    pItem->MinWoodCount();
                }
                else if (stage_[bufX][bufZ - 4].type == LOG)
                {
                    stage_[bufX][bufZ + 1].type = BRIDGE;
                    stage_[bufX][bufZ].type = BRIDGE;
                    stage_[bufX][bufZ - 1].type = BRIDGE;
                    stage_[bufX][bufZ].type = BRIDGE;
                    stage_[bufX][bufZ - 3].type = BRIDGE;
                    PopBridgeEffect();
                    pItem->MinWoodCount();
                }
                else if (stage_[bufX][bufZ - 5].type == LOG)
                {
                    stage_[bufX][bufZ].type = BRIDGE;
                    stage_[bufX][bufZ - 1].type = BRIDGE;
                    stage_[bufX][bufZ - 2].type = BRIDGE;
                    stage_[bufX][bufZ - 1].type = BRIDGE;
                    stage_[bufX][bufZ - 4].type = BRIDGE;
                    PopBridgeEffect();
                    pItem->MinWoodCount();
                }
            }
        }
    }
    else
    {
        // 前のフレームであったガイドの橋を消す
        for (int i = 0; i < 5; i++)
        {
            stage_[buf[i].x][buf[i].z].type = EMPTY;
        }

        for (int x = bridgeRimit_; x < STAGE_SIZE_X - bridgeRimit_; x++)
        {
            for (int z = ZERO; z < STAGE_SIZE_Z; z++)
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
                    SetStageType(bufX, bufZ, BRIDGE_FADE);
                    SetStageType(bufX, bufZ + 1, BRIDGE_FADE);
                    SetStageType(bufX, bufZ + 2, BRIDGE_FADE);
                    SetStageType(bufX, bufZ + 3, BRIDGE_FADE);
                    SetStageType(bufX, bufZ + 4, BRIDGE_FADE);

                    buf[0] = XMINT3(bufX, 1, bufZ);
                    buf[1] = XMINT3(bufX, 1, bufZ + 1);
                    buf[2] = XMINT3(bufX, 1, bufZ + 2);
                    buf[3] = XMINT3(bufX, 1, bufZ + 3);
                    buf[4] = XMINT3(bufX, 1, bufZ + 4);
                }
                else if (stage_[bufX][bufZ - 2].type == LOG)
                {
                    SetStageType(bufX, bufZ, BRIDGE_FADE);
                    SetStageType(bufX, bufZ - 1, BRIDGE_FADE);
                    SetStageType(bufX, bufZ + 1, BRIDGE_FADE);
                    SetStageType(bufX, bufZ + 2, BRIDGE_FADE);
                    SetStageType(bufX, bufZ + 3, BRIDGE_FADE);

                    buf[0] = XMINT3(bufX, 1, bufZ - 1);
                    buf[1] = XMINT3(bufX, 1, bufZ);
                    buf[2] = XMINT3(bufX, 1, bufZ + 1);
                    buf[3] = XMINT3(bufX, 1, bufZ + 2);
                    buf[4] = XMINT3(bufX, 1, bufZ + 3);
                }
                else if (stage_[bufX][bufZ - 3].type == LOG)
                {
                    SetStageType(bufX, bufZ + 2, BRIDGE_FADE);
                    SetStageType(bufX, bufZ + 1, BRIDGE_FADE);
                    SetStageType(bufX, bufZ, BRIDGE_FADE);
                    SetStageType(bufX, bufZ - 1, BRIDGE_FADE);
                    SetStageType(bufX, bufZ - 2, BRIDGE_FADE);

                    buf[0] = XMINT3(bufX, 1, bufZ + 2);
                    buf[1] = XMINT3(bufX, 1, bufZ + 1);
                    buf[2] = XMINT3(bufX, 1, bufZ);
                    buf[3] = XMINT3(bufX, 1, bufZ - 1);
                    buf[4] = XMINT3(bufX, 1, bufZ - 2);
                }
                else if (stage_[bufX][bufZ - 4].type == LOG)
                {
                    SetStageType(bufX, bufZ + 1, BRIDGE_FADE);
                    SetStageType(bufX, bufZ, BRIDGE_FADE);
                    SetStageType(bufX, bufZ - 1, BRIDGE_FADE);
                    SetStageType(bufX, bufZ - 2, BRIDGE_FADE);
                    SetStageType(bufX, bufZ - 3, BRIDGE_FADE);

                    buf[0] = XMINT3(bufX, 1, bufZ + 1);
                    buf[1] = XMINT3(bufX, 1, bufZ);
                    buf[2] = XMINT3(bufX, 1, bufZ - 1);
                    buf[3] = XMINT3(bufX, 1, bufZ - 2);
                    buf[4] = XMINT3(bufX, 1, bufZ - 3);
                }
                else if (stage_[bufX][bufZ - 5].type == LOG)
                {
                    SetStageType(bufX, bufZ, BRIDGE_FADE);
                    SetStageType(bufX, bufZ - 1, BRIDGE_FADE);
                    SetStageType(bufX, bufZ - 2, BRIDGE_FADE);
                    SetStageType(bufX, bufZ - 3, BRIDGE_FADE);
                    SetStageType(bufX, bufZ - 4, BRIDGE_FADE);

                    buf[0] = XMINT3(bufX, 1, bufZ);
                    buf[1] = XMINT3(bufX, 1, bufZ - 1);
                    buf[2] = XMINT3(bufX, 1, bufZ - 2);
                    buf[3] = XMINT3(bufX, 1, bufZ - 3);
                    buf[4] = XMINT3(bufX, 1, bufZ - 4);
                }
            }
        }
    }
}

void Stage::PopBridgeEffect()
{
    effectPos_ = { (float)bufX, 1.f, (float)bufZ };
    StageEffect::PopBridgeEffect(effectPos_);
    StageAudio::PopStageAudio();
}

void Stage::RandStage()
{
    //マップの自動生成
    while(bridgeCount_ < MAX_RAND_BRIDGE)
    {
        int randX = (rand() % STAGE_SIZE_X - bridgeRimit_);
        int randZ = (rand() % STAGE_SIZE_Z - bridgeRimit_);

        if (randZ == 27 || randZ == 21 || randZ == 15 || randZ == 9)
        {
            stage_[randX][randZ + 2].type = BRIDGE;
            stage_[randX][randZ + 1].type = BRIDGE;
            stage_[randX][randZ].type = BRIDGE;
            stage_[randX][randZ - 1].type = BRIDGE;
            stage_[randX][randZ - 2].type = BRIDGE;
            bridgeCount_++;
        }
    }
}

bool Stage::IsBridge(int x,  int z)
{
    return (stage_[x][z].type == BRIDGE);
}

bool Stage::IsCorner(int x,  int z)
{
    return (stage_[x][z].type == CORNER);
}