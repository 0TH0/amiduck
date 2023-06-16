#include "EnemyMob.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Engine/Astar.h"
#include "Engine/Model.h"
#include "Stage.h"

static XMFLOAT3 trans;

//コンストラクタ
EnemyMob::EnemyMob(GameObject* parent)
    :GameObject(parent, "EnemyMob"),hModel_(-1)
{
}

//デストラクタ
EnemyMob::~EnemyMob()
{
}

void EnemyMob::Initialize()
{
    hModel_ = Model::Load("Model\\fire\\fireball.fbx");
    transform_.position_ = { 0, 1.5f, 10.f };

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.75f);
    AddCollider(collision);

    pParticle_ = Instantiate<Particle>(this);

    //炎
    data.textureFileName = "Image\\Cloud.png";
    data.positionErr = XMFLOAT3(0.1, 0, 0.1);
    data.delay = 0;
    data.number = 1;
    data.lifeTime = 60;
    //data.gravity = -0.002f;
    data.dir = XMFLOAT3(0, 1, 0);
    data.dirErr = XMFLOAT3(0, 0, 0);
    data.speed = 0.01f;
    data.speedErr = 0.0;
    data.size = XMFLOAT2(1.5, 1.5);
    data.sizeErr = XMFLOAT2(0.4, 0.4);
    data.scale = XMFLOAT2(1.01, 1.01);
    data.color = XMFLOAT4(1, 1, 0, 1);
    data.deltaColor = XMFLOAT4(0, -0.03, 0, -0.02);
}

void EnemyMob::Update()
{
    Stage* pStage = (Stage*)FindObject("Stage");

    for (int x = 0; x < STAGE_SIZE_X; x++)
    {
        for (int z = 0; z < STAGE_SIZE_Z; z++)
        {
            AI_.SetMapType(pStage->GetStageType(x, z), x, z);
        }
    }

    data.position = transform_.position_;
    pParticle_->Start(data);

    transform_.rotate_.y += 5;
    Action();
}

void EnemyMob::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void EnemyMob::Release()
{
}

void EnemyMob::Action()
{
    Player* pPlayer = (Player*)FindObject("Player");
    
    if (CanMove_)
    {
        if (totalCell >= 0)
        {
            XMVECTOR v = { (float)AI_.GetToGoalCell(totalCell).x, 1.5f, (float)AI_.GetToGoalCell(totalCell).z, 0 };

            //XMStoreFloat3(&transform_.position_, XMVectorLerp(XMLoadFloat3(&transform_.position_), v, 0.4f));

            transform_.position_ = VectorToFloat3(v);
        }
    }

    //何フレーム毎に進むか
    int frame = 7;

    if (count_ > frame)
    {
        int PlayerPosX = (int)pPlayer->GetPosition().x;
        int PlayerPosZ = (int)pPlayer->GetPosition().z;
        trans = pPlayer->GetPosition();

        //プレイヤーを探索
        if (AI_.Search({ (int)transform_.position_.x, (int)transform_.position_.z }, { PlayerPosX, PlayerPosZ }))
        {
            totalCell = AI_.GetToGoalTotalCell();
            CanMove_ = true;
        }

        count_ = 0;
    }
    count_++;
}

void EnemyMob::OnCollision(GameObject* pTarget)
{
    //if (pTarget->GetObjectName() == "Player")
    //{
    //    SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
    //    pSceneManager->ChangeScene(SCENE_ID_RESULT);
    //}
}