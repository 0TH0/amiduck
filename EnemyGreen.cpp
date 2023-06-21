#include "EnemyGreen.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Engine/Astar.h"
#include "Engine/Model.h"
#include "Stage.h"

//�R���X�g���N�^
EnemyGreen::EnemyGreen(GameObject* parent)
    :GameObject(parent, "EnemyGreen"), hModel_(-1)
{
}

//�f�X�g���N�^
EnemyGreen::~EnemyGreen()
{
}

void EnemyGreen::Initialize()
{
    hModel_ = Model::Load("Model\\fire\\fireBallGreen.fbx");
    transform_.position_ = { 0, 1.5f, 10.f };

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.75f);
    AddCollider(collision);
}

void EnemyGreen::Update()
{
    Stage* pStage = (Stage*)FindObject("Stage");

    for (int x = 0; x < STAGE_SIZE_X; x++)
    {
        for (int z = 0; z < STAGE_SIZE_Z; z++)
        {
            AI_.SetMapType(pStage->GetStageType(x, z), x, z);
        }
    }


    transform_.rotate_.y += 5;
    Action();
}

void EnemyGreen::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void EnemyGreen::Release()
{
}

void EnemyGreen::Action()
{
    Player* pPlayer = (Player*)FindObject("Player");

    if (CanMove_)
    {
        if (totalCell >= 0)
        {
            XMVECTOR v = { (float)AI_.GetToGoalCell(totalCell).x, 1.5f, (float)AI_.GetToGoalCell(totalCell).z, 0 };

            XMStoreFloat3(&transform_.position_, XMVectorLerp(XMLoadFloat3(&transform_.position_), v, 0.4f));

            transform_.position_ = VectorToFloat3(v);
        }
    }

    //�S�[���ɒ�������
    if (!AI_.GetExistMinNode())
    {
        randX_ = rand() % STAGE_SIZE_X + 1;
        randZ_ = rand() % STAGE_SIZE_Z + 1;
    }

    //���t���[�����ɐi�ނ�
    int frame = 7;

    if (count_ > frame)
    {
        int PlayerPosX = (int)pPlayer->GetPosition().x;
        int PlayerPosZ = (int)pPlayer->GetPosition().z;

        //�v���C���[��T��
        if (AI_.Search({ (int)transform_.position_.x, (int)transform_.position_.z }, { randX_, randZ_ }))
        {
            totalCell = AI_.GetToGoalTotalCell();
            CanMove_ = true;
        }

        count_ = 0;
    }
    count_++;
}