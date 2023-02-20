#include "Player.h"
#include "Stage.h"
#include "PlayScene.h"
#include "StartScene.h"
#include "Fire.h"
#include "FireFollowGround.h"
#include "Controller.h"
#include "Enemy.h"
#include "Line.h"
#include "Mushroom.h"

#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"

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

    //�|�����C��������
    pLine = new PoryLine;
    pLine->Load("tex_red.png");

    pLine2 = new PoryLine;
    pLine2->Load("tex_orange.png");
}

void Player::Update()
{
    // 1�t���[���O�̍��W
    prevPosition = XMLoadFloat3(&transform_.position_);

    LadderLottery();

    if (Input::IsKeyDown(DIK_Q))
    {
       Instantiate<FireFollowGround>(GetParent());
    }

    if (Input::IsKeyDown(DIK_E))
    {
       Instantiate<Fire>(GetParent());
    }

    if (Input::IsKeyDown(DIK_W))
    {
        //����n���Ă��Ȃ�������
        if (!(IsOnBridge_) && hasItem_)
        {
            IsSpeedUp_ = true;
            Instantiate<Line>(this);
            hasItem_ = false;
        }
    }

    if (IsSpeedUp_)
    {
        SpeedUpTime_++;
        speed_ = 0.4;
    }
    if (SpeedUpTime_ > 60)
    {
        IsSpeedUp_ = false;
        SpeedUpTime_ = 0;
    }

    pStage = (Stage*)FindObject("Stage");
    Enemy* pEnemy = (Enemy*)FindObject("Enemy");

    RotateDirMove();

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
    if (Input::IsKeyDown(DIK_SPACE) && transform_.position_.y <= 0.75f) //&& (IsJump == 0))
    {
        //�����x
        jump_v0 = 0.2;
        //�d��
        gravity = 0.008f;

        //�����x��������
        move_.y = jump_v0;

        //�d�͂�������
        move_.y += gravity;

        //�W�����v�t���O
        IsJump = true;
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
    else if(starTime_ > 0)
    {
        starTime_++;
    }

    if (starNum_ >= 5)
    {
        starNum_ = 5;
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_CLEAR);
    }
}

void Player::Draw()
{
    Model::SetTransform(hModel2_, transform_);
    Model::SetTransform(hModel_, transform_);

    switch (playerState)
    {
    case EGG:
        Model::FlashModel(hModel_);
        break;
    case LARVA:
        Model::FlashModel(hModel2_);
        break;
    }

    pText->Draw(100, 100, "Player:");
    pText->Draw(250, 100, starNum_);

    if (IsSpeedUp_)
    {
        pLine2->AddPosition(transform_.position_);
        pLine2->Draw();
    }
}

void Player::Release()
{
    //�|�����C�����
    pLine->Release();
    pLine2->Release();
}

//�����ɓ�������
void Player::OnCollision(GameObject* pTarget)
{
    //�G�ɓ�������
    if (pTarget->GetObjectName() == "Enemy")
    {
        Model::SetIsFlash(hModel_);
        Model::SetIsFlash(hModel2_);

        if (starTime_ == 0)
        {
            if (starNum_ > 0)
            {
                starTime_++;
                starNum_--;
            }
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

    XMVECTOR vPlayerPos = XMLoadFloat3(&transform_.position_);
    XMVECTOR Down = { 0,-1,0,0 };

    //�G�ɓ�������
    if (pTarget->GetObjectName() == "Mushroom")
    {
        //�G�̈ʒu
        XMFLOAT3 EnemyPos = pTarget->GetPosition();
        XMVECTOR vEnemyPos = XMLoadFloat3(&EnemyPos);

        //�v���C���[�̈ʒu
        XMVECTOR PlayerPos = vEnemyPos - vPlayerPos;
        XMVector3Normalize(PlayerPos);

        //Down�ƃv���C���[�̊O�ς����߂�
        XMVECTOR vDot = XMVector3Dot(Down, PlayerPos);
        float Dot = XMVectorGetY(vDot);

        //�p�x�����߂�
        angle = acos(Dot) * (180.0 / 3.14f);

        if (angle <= 90)
        {
            //�����x
            jump_v0 = 0.15f;
            //�d��
            gravity = 0.003f;

            //�����x��������
            move_.y = jump_v0;
            transform_.position_.y += move_.y;

            //�d�͂�������
            move_.y += gravity;
            transform_.position_.y += move_.y;
        }
        else
        {
            //�����瓖��������v���C���[������
            SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
            pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
        }
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
            case Player::EGG:
                speed_ = 0.2;
                break;
            case Player::LARVA:
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
                case Player::EGG:
                    speed_ = 0.2;
                    break;                                                                                    
                case Player::LARVA:
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

void Player::RotateDirMove()
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
