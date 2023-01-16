#include "Player.h"
#include "Stage.h"
#include "PlayScene.h"
#include "StartScene.h"
#include "Fire.h"
#include "Controller.h"
#include "Enemy.h"
#include "Line.h"

#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"


//////////////////////////////////////////////////////////////////////

// 215�s�ڂ� LadderLottery()
// ���[���x�[�XAI
// �v���C���[�̉E�ɋ��̃I�u�W�F�N�g������ΉE��
// ���ɋ��̃I�u�W�F�N�g������΍��ɍs���悤�ɂȂ��Ă܂�
// �����E�ɋ�������ꍇ�͉E�D��(�ł���΃����_���ł���\��)

//////////////////////////////////////////////////////////////////////





//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),

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
Player::~Player()
{
}

//������
void Player::Initialize()
{
    hModel_ = Model::Load("Model\\Player\\egg.fbx");
    assert(hModel_ >= 0);

    hModel2_ = Model::Load("Model\\Player\\duck.fbx");
    assert(hModel2_ >= 0);

    //�A�j���[�V�����̐ݒ�
    Model::SetAnimFrame(hModel_, 0, 200, 1.0f);

    //�ʒu
    //transform_.position_ = XMFLOAT3(0, 0.8, 38);
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
}

void Player::Update()
{
    LadderLottery();

    if (Input::IsKeyDown(DIK_SPACE))
    {
        //����n���Ă��Ȃ�������
        if (!(IsOnBridge_))
        {
            IsSpeedUp_ = true;
            Instantiate<Line>(this);
        }
    }

    if (IsSpeedUp_)
    {
        SpeedUpTime_++;
        speed_ = 0.4;
    }
    if (SpeedUpTime_ > 30)
    {
        IsSpeedUp_ = false;
    }

    pStage = (Stage*)FindObject("Stage");
    Enemy* pEnemy = (Enemy*)FindObject("Enemy");

    // 1�t���[���O�̍��W
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);

    //��~����
    if (Input::IsKeyDown(DIK_F))
    {
        if (!IsStop_)
        {
            speed_ = 0;
            IsStop_ = true;
        }
        else
        {
            speed_ = 0.3f;
            IsStop_ = false;
        }
    }

    /////////////////////////�ړ�/////////////////////////

    //�W�����v���̏d��
    //if (IsJump)
    //{
    //    //�d��
    //    move_.y -= gravity;
    //    transform_.position_.y += move_.y;
    //}

    //�W�����v���ĂȂ����̏d��
    //else
    //{
    //    //�d��
    //    gravity = 0.1f;

    //    //�d�͂�������
    //    move_.y = -gravity;
    //    transform_.position_.y += move_.y;
    //}

    if (Input::IsKeyDown(DIK_Z))
    {
        Camera::SetDual();
    }
    if (Input::IsKeyDown(DIK_X))
    {
        Camera::SetDefault();
    }
    if (Input::IsKeyDown(DIK_C))
    {
        speed_ = -0.2;
    }
    if (Input::IsKeyDown(DIK_V))
    {
        speed_ = 0.2;
    }

    if (!IsBlend())
    {
        if (Input::IsKeyDown(DIK_L))
        {
            Blend();
            EmitterData data;
            data.textureFileName = "Particle\\Cloud.png";
            data.position = transform_.position_;
            data.positionErr = XMFLOAT3(0.1f, 0, 0.1f);
            data.delay = 0;
            data.number = 5;
            data.lifeTime = 60;
            data.dir = XMFLOAT3(0, 1, 0);
            data.dirErr = XMFLOAT3(0, 0, 0);
            data.speed = 0.01f;
            data.speedErr = 0.0;
            data.size = XMFLOAT2(2, 2);
            data.sizeErr = XMFLOAT2(0.4, 0.4);
            data.scale = XMFLOAT2(1.03, 1.02);
            data.color = XMFLOAT4(0.7, 0.7, 0.7, 0.1f);
            pParticle_->Start(data);
        }
    }
    if (Input::IsKeyUp(DIK_L))
    {
        Default();
    }
}

void Player::Draw()
{
    Model::SetTransform(hModel2_, transform_);
    Model::SetTransform(hModel_, transform_);

    switch (playerState)
    {
    case EGG:
        Model::Draw(hModel_);
        break;
    case LARVA:
        Model::Draw(hModel2_);
        break;
    }
}

void Player::Release()
{
}

//�����ɓ�������
void Player::OnCollision(GameObject* pTarget)
{
    //�G�ɓ�������
    if (pTarget->GetObjectName() == "Enemy")
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
    }

    if (pTarget->GetObjectName() == "Star")
    {
        playerState = LARVA;
    }
}

//���݂�����
void Player::LadderLottery()
{
    //////////////////�ǂƂ̏Փ˔���///////////////////////
    int objX = transform_.position_.x;
    int objY = transform_.position_.y;
    int objZ = transform_.position_.z;

    ////�ǂ̔���(��)
    if (pStage->IsWall(objX, objZ) || pStage->IsBridge(objX, objZ))
    {
        transform_.position_.y = (int)(transform_.position_.y) + 0.8;
        IsJump = 0;
    }

    if (!IsRight_ && !IsLeft_)
    {
        //�i�s�����ɓ����Ȃ�������߂��Ă���
        if (pStage->IsEmpty((float)objX + 3, objZ))
        {
            IsReturn_ = true;
            transform_.rotate_ = XMFLOAT3(0, 0, 0);
        }
        if (pStage->IsEmpty((float)objX - 3, objZ))
        {
            IsReturn_ = false;
            transform_.rotate_ = XMFLOAT3(0, 180, 0);
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
            case Player::EGG:
                speed_ = 0.2;
                break;
            case Player::LARVA:
                speed_ = 0.3f;
                break;
            default:
                break;
            }

            if (IsReturn_)
            {
                transform_.rotate_ = XMFLOAT3(0, 0, 0);
            }
            else
            {
                transform_.rotate_ = XMFLOAT3(0, 180, 0);
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
            transform_.rotate_ = XMFLOAT3(0, 90, 0);
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
                case Player::EGG:
                    speed_ = 0.2;
                    break;                                                                                    
                case Player::LARVA:
                    speed_ = 0.3f;
                    break;
                default:
                    break;
                }
                if (IsReturn_)
                {
                    transform_.rotate_ = XMFLOAT3(0, 0, 0);
                }
                else
                {
                    transform_.rotate_ = XMFLOAT3(0, 180, 0);
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