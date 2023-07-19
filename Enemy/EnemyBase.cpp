#include "EnemyBase.h"
#include "../Engine/Collider.h"
#include "../Engine/Model.h"

namespace
{
    static const int ROTATE_SPEED = 5;      //��]���x
    static const float DIF_GOAL = 0.3f;     //�ړI�n�܂ł̌덷����
    static const float POSY = 1.5f;         //Y���W
    static const float LERP = 0.2f;         //��Ԃ���l
    static const float CENTER = 0.5f;       //�����蔻��T�C�Y
}

EnemyBase::EnemyBase(GameObject* parent, std::string name)
    : GameObject(parent, name), hModel_(-1),frame_(7),frameCount_(0),
      AI_(),CanMove_(false),totalCell(0),v(),pPlayer_(nullptr)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize()
{
    hModel_ = Model::Load("Model\\fire.fbx");

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(ZERO, ZERO, ZERO), CENTER);
    AddCollider(collision);

    //������
    InitBase();
}

void EnemyBase::Update()
{
    pPlayer_ = (Player*)FindObject("Player");
    Stage* pStage = (Stage*)FindObject("Stage");

    //���݂̃X�e�[�W�����Z�b�g
    for (int x = ZERO; x < STAGE_SIZE_X; x++)
    {
        for (int z = ZERO; z < STAGE_SIZE_Z; z++)
        {
            AI_.SetMapType(pStage->GetStageType(x, z), x, z);
        }
    }

    //��]
    transform_.rotate_.y += ROTATE_SPEED;

    //�e�s��
    Action();
}

void EnemyBase::Draw()
{
    Model::SetTransform(hModel_, transform_);
    //�e�F�ύX
    ChangeColor();
    Model::Draw(hModel_);
}

void EnemyBase::Release()
{
    ReleaseBase();
}

void EnemyBase::Move()
{
    //�ړI�n�ɒ����Ă��Ȃ��ꍇ
    if (CanMove_ && totalCell >= ZERO)
    {
        //�ړI�n�܂ł̃x�N�g��
        v = { (float)AI_.GetToGoalCell(totalCell).x + DIF_GOAL, POSY, (float)AI_.GetToGoalCell(totalCell).z + DIF_GOAL, 0 };

        //���`���
        XMStoreFloat3(&transform_.position_, XMVectorLerp(XMLoadFloat3(&transform_.position_), v, LERP));
    }
}

void EnemyBase::Search(CELL goal)
{
    //�t���[�����t���[���J�E���g�𒴂�����
    if (frameCount_ > frame_)
    {
        int PlayerPosX = (int)pPlayer_->GetPosition().x;
        int PlayerPosZ = (int)pPlayer_->GetPosition().z;
        //�v���C���[��T��
        if (AI_.Search({ (int)transform_.position_.x, (int)transform_.position_.z }, goal))
        {
            totalCell = AI_.GetToGoalTotalCell();
            CanMove_ = true;
        }
        frameCount_ = 0;
    }
    frameCount_++;
}