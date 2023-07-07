#include "CharacterBase.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"

CharacterBase::CharacterBase(GameObject* parent, std::string name)
	: GameObject(parent, name),pStage(nullptr), data(), prevPosition(), 
      status_(EGG), jump_v0(),gravity(0),angle(0),move_(),speed_(0.3f),SpeedUpTime_(0),
      IsJump(false), IsGround(false), IsEnemy(false), IsReturn_(false), IsSpeedUp_(false),IsRight_(false),IsLeft_(false),
      IsStop_(false), IsOnBridge_(false),
      delay_(0),StoppedTime_(0),hasItem_(0),speedChange_(0.2f)
{
    for (int i = 0; i < Status::STATUS_MAX; i++)
    {
        hModel_[i] = -1;
    }

    for (int i = 0; i < DIR_MAX; i++)
    {
        SpeedOnWood_[i] = 0;
        TimeOnWood_[i] = 0;
    }
}

//�f�X�g���N�^
CharacterBase::~CharacterBase()
{
}

//������
void CharacterBase::Initialize()
{
	InitBase();
}

//�X�V
void CharacterBase::Update()
{
    pStage = (Stage*)FindObject("Stage");

    switch (status_)
    {
    case EGG:
        transform_.rotate_.z += 10;
        break;
    case GROWN:
        transform_.rotate_ = XMFLOAT3(0, 180, 0);
        break;
    default:
        break;
    }

    if (!IsStop_)
    {
        ////�W�����v���̏d��
        if (IsJump)
        {
            //�d��
            move_.y -= gravity;
            transform_.position_.y += move_.y;
        }
        //�W�����v���ĂȂ����̏d��
        else
        {
            //�d��
            gravity = 0.1f;

            //�d�͂�������
            move_.y = -gravity;
            transform_.position_.y += move_.y;
        }
    }

    if (transform_.position_.y <= 0.75f)
    {
        transform_.position_.y = 0.75f;
    }

    Command();
    Action();

    // 1�t���[���O�̍��W
    prevPosition = XMLoadFloat3(&transform_.position_);

    //���݂������̏���
    LadderLottery();

    //�i�s�����ɉ�]����
    RotateDirMove();
}

//�`��
void CharacterBase::Draw()
{
	DrawBase();
}

//�J��
void CharacterBase::Release()
{
}

void CharacterBase::LadderLottery()
{
    //////////////////�ǂƂ̏Փ˔���///////////////////////
    XMINT3 obj = ToXMINT({ transform_.position_ .x + 0.4f, transform_.position_.y ,transform_.position_.z });

    //�ǂ̔���(��)
    if (!IsRight_ && !IsLeft_)
    {
        //�i�s�����ɓ����Ȃ�������߂��Ă���
        if (pStage->IsCorner(obj.x + 1, obj.z))
        {
            IsReturn_ = true;
        }
        if (pStage->IsCorner(obj.x - 1, obj.z))
        {
            IsReturn_ = false;
        }
    }

    if (transform_.position_.x <= 0)
    {
        IsReturn_ = false;
    }

    if (IsReturn_)
    {
        transform_.position_.x -= speed_;
    }
    else
    {
        transform_.position_.x += speed_;
    }


    ///////////////////////// ���݂������̏��� ///////////////////////////////////////////
    if (!IsLeft_ && StoppedTime_ > 5)
    {
        if (pStage->IsBridge(obj.x, obj.z - 1))
        {
            speed_ = 0;
            IsRight_ = true;
            StoppedTime_ = 0;
            IsOnBridge_ = true;
        }
    }

    //�E�ɍs��
    if (IsRight_)
    {
        IsStop_ = false;
        SpeedOnWood_[R] = 0.2;
        TimeOnWood_[R] += SpeedOnWood_[R];

        if (TimeOnWood_[R] >= 6)
        {
            TimeOnWood_[R] = 0;
            IsRight_ = false;
            IsOnBridge_ = false;
            delay_ = 0;
            SpeedOnWood_[R] = 0;

            switch (status_)
            {
            case EGG:
                speed_ = speedChange_;
                break;
            case GROWN:
                speed_ = speedChange_ * 2;
                break;
            default:
                break;
            }
        }
        else
        {
            //���Ɉړ�
            transform_.position_.z -= SpeedOnWood_[R];
        }
    }

    //���ɍs��
    else
    {
        //�~�܂��Ă��Ȃ�������
        if (!IsStop_)
        {
            StoppedTime_++;

            if (!IsLeft_) delay_++;
        }

        //�E�ɍs���Ă��炷���ɍ��ɍs���Ȃ��悤�ɊԊu���J����
        if (delay_ > 5)
        {
            if (pStage->IsBridge(obj.x, obj.z + 3))
            {
                speed_ = 0;

                IsLeft_ = true;
                IsOnBridge_ = true;
            }
        }

        if (IsLeft_)
        {
            IsStop_ = false;
            SpeedOnWood_[L] = 0.2;
            TimeOnWood_[L] += SpeedOnWood_[L];

            if (TimeOnWood_[L] >= 6)
            {
                TimeOnWood_[L] = 0;
                IsLeft_ = false;
                IsOnBridge_ = false;
                delay_ = 0;
                StoppedTime_ = 0;
                SpeedOnWood_[L] = 0;

                switch (status_)
                {
                case EGG:
                    speed_ = speedChange_;
                    break;
                case GROWN:
                    speed_ = speedChange_ * 2;
                    break;
                default:
                    break;
                }
            }
            else
            {
                //�E�Ɉړ�
                transform_.position_.z += SpeedOnWood_[L];
            }
        }
    }
}

void CharacterBase::RotateDirMove()
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
		XMVECTOR front = { -1, 0, 0, 0 };

		//front��move�̓��ς����߂�
		XMVECTOR vecDot = XMVector3Dot(front, move);
		float dot = XMVectorGetX(vecDot);

		//�����Ă�p�x�����߂�i���W�A���j
		float angle = acos(dot);

		//front��move�̊O�ς����߂�
		XMVECTOR cross = XMVector3Cross(front, move);

		//�O�ς̌��ʂ�Y���}�C�i�X�@���@�������@���@���ɐi��ł�
		if (XMVectorGetY(cross) < 0)
		{
			angle *= -1;
		}

		//���̂Ԃ��]������
		transform_.rotate_.y = angle * 180.0f / 3.14f;
	}
}