#include "EnemyBase.h"
#include "../Engine/Collider.h"
#include "../Engine/Model.h"

namespace
{
    static const int ROTATE_SPEED = 5;      //��]���x
    static const float DIF_GOAL = 0.3f;     //�ړI�n�܂ł̌덷����
    static const float POSY = 0.7f;         //Y���W
    static const float LERP = 0.2f;         //��Ԃ���l
    static const float RADIUS = 0.5f;       //�����蔻��T�C�Y
    XMFLOAT3 pos;
}

EnemyBase::EnemyBase(GameObject* parent, std::string name)
    : GameObject(parent, name), hModel_(-1),frameMove_(7),frameCount_(0),
      AI_(),CanMove_(false),totalCell_(0),v_(),pPlayer_(nullptr),prevPosition()
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize()
{
    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(ZERO, ZERO, ZERO), RADIUS);
    AddCollider(collision);

    transform_.position_.y = POSY;

    //������
    InitBase();
}

void EnemyBase::Update()
{
    prevPosition = XMLoadFloat3(&transform_.position_);
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

    //�e�s��
    Action();

    RotateDirMove();
}

void EnemyBase::Draw()
{
    Model::SetOutLineDrawFlag(hModel_, true);
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
    if (CanMove_ && totalCell_ >= 0)
    {
        //�ړI�n�܂ł̃x�N�g��
        v_ = { (float)AI_.GetToGoalCell(totalCell_).x + DIF_GOAL, POSY, (float)AI_.GetToGoalCell(totalCell_).z + DIF_GOAL, 0 };

        pos = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&transform_.position_), v_, LERP));
        //���`���
        transform_.position_ = pos;
    }
}

void EnemyBase::RotateDirMove()
{
    //���݂̈ʒu�x�N�g��
    XMVECTOR nowPosition = XMLoadFloat3(&transform_.position_);

    //����̈ړ��x�N�g��
    XMVECTOR move = nowPosition - prevPosition;

    //�ړ��x�N�g���̒����𑪂�
    XMVECTOR length = XMVector3Length(move);

    //0.1�ȏ�ړ����Ă��Ȃ��]����
    if (XMVectorGetX(length) > 0.1f)
    {
        //�p�x�����߂邽�߂ɒ������P�ɂ���i���K���j
        move = XMVector3Normalize(move);

        //��ƂȂ鉜�����̃x�N�g��
        XMVECTOR front = { 0, 0, 1, 0 };

        //front��move�̓��ς����߂�
        XMVECTOR vecDot = XMVector3Dot(front, move);
        float dot = XMVectorGetX(vecDot);

        //�����Ă�p�x�����߂�i���W�A���j
        float angle_ = acos(dot);

        //front��move�̊O�ς����߂�
        XMVECTOR cross = XMVector3Cross(front, move);

        //�O�ς̌��ʂ�Y���}�C�i�X�@���@�������@���@���ɐi��ł�
        if (XMVectorGetY(cross) < 0)
        {
            angle_ *= -1;
        }

        //���̂Ԃ��]������
        transform_.rotate_.y = angle_ * PI_DEGREES / M_PI;
    }
}

void EnemyBase::Search(CELL goal)
{
    //�t���[�����t���[���J�E���g�𒴂�����
    if (frameCount_ > frameMove_)
    {
        //�v���C���[��T��
        if (AI_.Search({ (int)transform_.position_.x, (int)transform_.position_.z }, goal))
        {
            totalCell_ = AI_.GetToGoalTotalCell();
            CanMove_ = true;
        }
        frameCount_ = 0;
    }
    frameCount_++;
}