#include "PlayScene.h"
#include "StartScene.h"
#include "Controller.h"
#include "Enemy.h"
#include "Line.h"
#include "Star.h"

#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy"),

    //�ϐ�
    hModel_(-1),
    jump_v0(0), gravity(0), angle(0), BossHp(3),

    //�t���O
    IsJump(false), IsGround(false),

    //�萔
    speed_(0.3f), DUSHSPEED(0.05f),
    CAMERA_POS_Y(-15.0f), CAMERA_TAR_Y(-5.0f)
{
}

//�f�X�g���N�^
Enemy::~Enemy()
{
}

//������
void Enemy::Initialize()
{
    hModel_ = Model::Load("Model\\Player\\egg.fbx");
    assert(hModel_ >= 0);

    hModel2_ = Model::Load("Model\\Enemy\\raccoon.fbx");
    assert(hModel2_ >= 0);

    //�A�j���[�V�����̐ݒ�
    Model::SetAnimFrame(hModel_, 0, 200, 1.0f);

    //�ʒu
    transform_.rotate_ = XMFLOAT3(0, 180, 0);
    transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
    AddCollider(collision);

    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);

    Instantiate<Controller>(this);

    pText->Initialize();

    pParticle_ = Instantiate<Particle>(this);

    //�ŏ��͗�����
    playerState = EGG;

    Model::SetColor(hModel_, XMFLOAT4(1, 1, 1, 1));
}

void Enemy::Update()
{
    // 1�t���[���O�̍��W
    prevPosition = XMLoadFloat3(&transform_.position_);

    LadderLottery();

    //if (Input::IsKeyDown(DIK_SPACE))
    //{
    //    //����n���Ă��Ȃ�������
    //    if (!(IsOnBridge_))
    //    {
    //        IsSpeedUp_ = true;
    //        Instantiate<Line>(this);
    //        hasItem_ = false;
    //    }
    //}

    //if (IsSpeedUp_)
    //{
    //    SpeedUpTime_++;
    //    speed_ = 0.4;
    //}
    //if (SpeedUpTime_ > 30)
    //{
    //    IsSpeedUp_ = false;
    //}

    pStage = (Stage*)FindObject("Stage");
    Enemy* pEnemy = (Enemy*)FindObject("Enemy");

    RotateDirMove();

    //��~����
    //if (Input::IsKeyDown(DIK_F))
    //{
    //    if (!IsStop_)
    //    {
    //        speed_ = 0;
    //        IsStop_ = true;
    //    }
    //    else
    //    {
    //        speed_ = 0.3f;
    //        IsStop_ = false;
    //    }
    //}

    /////////////////////////�ړ�/////////////////////////
    //�W�����v���̏d��
    //if (Input::IsKey(DIK_Q)) //&& (IsJump == 0))
    //{
    //    //�����x
    //    jump_v0 = 0.2;
    //    //�d��
    //    gravity = 0.008f;

    //    //�����x��������
    //    move_.y = jump_v0;

    //    //�d�͂�������
    //    move_.y += gravity;

    //    //�W�����v�t���O
    //    IsJump = 1;
    //}

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

    //if (Input::IsKeyDown(DIK_Z))
    //{
    //    Camera::SetDual();
    //}
    //if (Input::IsKeyDown(DIK_X))
    //{
    //    Camera::SetDefault();
    //}

    //if (!IsBlend())
    //{
    //    if (Input::IsKeyDown(DIK_L))
    //    {
    //        Blend();
    //        EmitterData data;
    //        data.textureFileName = "Particle\\Cloud.png";
    //        data.position = transform_.position_;
    //        data.positionErr = XMFLOAT3(0.1f, 0, 0.1f);
    //        data.delay = 0;
    //        data.number = 5;
    //        data.lifeTime = 60;
    //        data.dir = XMFLOAT3(0, 1, 0);
    //        data.dirErr = XMFLOAT3(0, 0, 0);
    //        data.speed = 0.01f;
    //        data.speedErr = 0.0;
    //        data.size = XMFLOAT2(2, 2);
    //        data.sizeErr = XMFLOAT2(0.4, 0.4);
    //        data.scale = XMFLOAT2(1.03, 1.02);
    //        data.color = XMFLOAT4(0.7, 0.7, 0.7, 0.1f);
    //        pParticle_->Start(data);
    //    }
    //}
    //if (Input::IsKeyUp(DIK_L))
    //{
    //    Default();
    //}

    if (starTime_ >= 10)
    {
        starTime_ = 0;
    }
    else if (starTime_ > 0)
    {
        starTime_++;
    }
}

void Enemy::Draw()
{
    Model::SetTransform(hModel2_, transform_);
    Model::SetTransform(hModel_, transform_);

    //���f���̐F
    switch (playerState)
    {
    case EGG:
        Model::FlashModel(hModel_);
        break;
    case LARVA:
        Model::FlashModel(hModel2_);
        break;
    }

    //pText->Draw(100, 200, "Enemy:");
    //pText->Draw(250, 200, starNum_);
}

void Enemy::Release()
{
}

//�����ɓ�������
void Enemy::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Fire" || pTarget->GetObjectName() == "FireFollowGround")
    {
        if (starTime_ == 0 && starNum_ > 0)
        {
            starTime_++;
            Model::SetIsFlash(hModel_);
            Model::SetIsFlash(hModel2_);
            starNum_--;
        }
    }

    //�G�ɓ�������
    if (pTarget->GetObjectName() == "Player")
    {
        if (starTime_ == 0)
        {
            starTime_++;
            Star* pStar = Instantiate<Star>(GetParent());
            Player* pPlayer = (Player*)FindObject("Player");
            pStar->SetPosition(pPlayer->GetPosition().x, pPlayer->GetPosition().y + 4, pPlayer->GetPosition().z);
        }
    }

    if (pTarget->GetObjectName() == "Star")
    {
        if (starTime_ == 0)
        {
            starTime_++;
            playerState = LARVA;
            starNum_++;
        }
    }
}

//���݂�����
void Enemy::LadderLottery()
{
    //////////////////�ǂƂ̏Փ˔���///////////////////////
    int objX = transform_.position_.x;
    int objY = transform_.position_.y;
    int objZ = transform_.position_.z;

    ////�ǂ̔���(��)
    //if (pStage->IsWall(objX, objZ) || pStage->IsBridge(objX, objZ))
    //{
    //    transform_.position_.y = (int)(transform_.position_.y) + 0.8;
    //    IsJump = 0;
    //}

    if (!IsRight_ && !IsLeft_)
    {
        //�i�s�����ɓ����Ȃ�������߂��Ă���
        if (pStage->IsEmpty((float)objX + 3, objZ))
        {
            IsReturn_ = true;
        }
        if (pStage->IsEmpty((float)objX - 3, objZ))
        {
            IsReturn_ = false;
        }
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

    if (!IsLeft_ && StoppedTime_ > 4)
    {
        if (pStage->IsBridge(objX, objZ - 3))
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
        transform_.rotate_ = XMFLOAT3(0, -90, 0);
        SpeedOnWood_[R] = 0.2;
        TimeOnWood_[R] += SpeedOnWood_[R];

        if (TimeOnWood_[R] >= 6)
        {
            TimeOnWood_[R] = 0;
            IsRight_ = false;
            IsOnBridge_ = false;
            delay_ = 0;
            SpeedOnWood_[R] = 0;


            switch (playerState)
            {
            case Enemy::EGG:
                speed_ = 0.2;
                break;
            case Enemy::LARVA:
                speed_ = 0.3f;
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
        if (delay_ > 4)
        {
            if (pStage->IsBridge(objX, objZ + 2))
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

                switch (playerState)
                {
                case Enemy::EGG:
                    speed_ = 0.2;
                    break;
                case Enemy::LARVA:
                    speed_ = 0.3f;
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

void Enemy::RotateDirMove()
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
