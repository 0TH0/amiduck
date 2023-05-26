#include "CharacterBase.h"
#include "CharacterBase.h"
#include "Stage.h"
#include "PlayScene.h"
#include "StartScene.h"
#include "Fire.h"
#include "FireFollowGround.h"
#include "Controller.h"
#include "Enemy.h"
#include "Line.h"
#include "Bomb.h"
#include "Item.h"
#include "Timer.h"
#include "Enemy.h"
#include "Observer/ResultObserver.h"

#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"
#include "Engine/Math.h"

static Timer* pTimer;

//�R���X�g���N�^
CharacterBase::CharacterBase(GameObject* parent)
    :GameObject(parent, "CharacterBase"),

    //�ϐ�
    hModel_(-1), hModel2_(-1),
    jump_v0(0), gravity(0), angle(0), delay_(0),

    //�t���O
    IsJump(false), IsGround(false), hasItem_(false), IsLeft_(false), IsRight_(false),

    //�萔
    speed_(0.3f), DUSHSPEED(0.05f),
    CAMERA_POS_Y(-15.0f), CAMERA_TAR_Y(-5.0f)
{
}

//�f�X�g���N�^
CharacterBase::~CharacterBase()
{
}

//������
void CharacterBase::Initialize()
{
    hModel_ = Model::Load("Model\\CharacterBase\\egg.fbx");
    assert(hModel_ >= 0);

    hModel2_ = Model::Load("Model\\CharacterBase\\duck.fbx");
    assert(hModel2_ >= 0);

    //�A�j���[�V�����̐ݒ�
    Model::SetAnimFrame(hModel_, 0, 200, 1.0f);

    //�ʒu
    transform_.rotate_ = XMFLOAT3(0, 180, 0);
    transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
    AddCollider(collision);

    Instantiate<Controller>(this);

    pParticle_ = Instantiate<Particle>(this);

    //�ŏ��͗�����
    CharacterBaseState = State::EGG;

    //�|�����C��������
    for (int i = 0; i < 3; i++)
    {
        pLine[i] = new PoryLine;
        pLine[i]->Load("Image\\tex_orange.png");
    }
}

void CharacterBase::Update()
{
    pTimer = (Timer*)FindObject("Timer");
    pStage = (Stage*)FindObject("Stage");
    Enemy* pEnemy = (Enemy*)FindObject("Enemy");

    switch (CharacterBaseState)
    {
    case CharacterBase::State::EGG:
        transform_.rotate_.z += 10;
        break;
    case CharacterBase::State::LARVA:
        transform_.rotate_ = XMFLOAT3(0, 180, 0);
        break;
    }

    //���̐����O�ȉ��ŗ�
    if (starNum_ <= 0)
    {
        CharacterBaseState = State::EGG;
    }
    else
    {
        CharacterBaseState = State::LARVA;
    }

    // 1�t���[���O�̍��W
    prevPosition = XMLoadFloat3(&transform_.position_);

    //���݂������̏���
    LadderLottery();

    //�i�s�����ɉ�]����
    RotateDirMove();

    //�A�C�e���g�p
    if (Input::IsKeyDown(DIK_E) && hasItem_)
    {
        Item* pItem = (Item*)FindObject("Item");
        switch (pItem->GetItem())
        {
            //�{�[���o��
        case Item::ItemNum::BALL:
            Instantiate<FireFollowGround>(GetParent());
            hasItem_ = false;
            pItem->SetItem(Item::ItemNum::ITEM_MAX);
            break;
            //���e�o��
        case Item::ItemNum::BOMB:
            Instantiate<Bomb>(GetParent());
            hasItem_ = false;
            pItem->SetItem(Item::ItemNum::ITEM_MAX);
            break;
        case Item::ItemNum::WING:
            //����n���Ă��Ȃ�������
            if (!(IsOnBridge_) && hasItem_)
            {
                //�_�b�V��
                IsSpeedUp_ = true;
                Instantiate<Line>(this);
                hasItem_ = false;
                pItem->SetItem(Item::ItemNum::ITEM_MAX);
            }
            break;
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
    if (Input::IsKeyDown(DIK_SPACE) && transform_.position_.y <= 0.75f)
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
    if (starTime_ >= 10)
    {
        starTime_ = 0;
    }
    else if (starTime_ > 0)
    {
        starTime_++;
    }
    //����5��邩��莞�Ԃ��o�߂�����
    if (starNum_ >= 5 || pTimer->GetRimit() <= 0)
    {
        Enemy* pEnemy = (Enemy*)FindObject("Enemy");

        //�G�̐��̐��̕�������������
        if (pEnemy->GetStarNum() >= starNum_)
        {
            ResultObserver::SetIsWin(false);
        }
        else
        {
            ResultObserver::SetIsWin(true);
        }
        //���U���g�V�[����
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_RESULT);
    }
}

void CharacterBase::Draw()
{
    Model::SetTransform(hModel2_, transform_);
    Model::SetTransform(hModel_, transform_);

    switch (CharacterBaseState)
    {
    case State::EGG:
        Model::FlashModel(hModel_);
        break;
    case State::LARVA:
        Model::FlashModel(hModel2_);
        break;
    }
    if (IsSpeedUp_)
    {
        float pos = -0.5f;
        for (int i = 0; i < 3; i++)
        {
            Transform trans = transform_;
            trans.position_.z += pos;
            pLine[i]->AddPosition(trans.position_);
            pLine[i]->SetWidth(0.1f);
            pLine[i]->SetColor(XMFLOAT4(1, 1, 1, 0.9));
            pLine[i]->Draw();
            pos += 0.5f;
        }
    }
}

void CharacterBase::Release()
{
    //�|�����C�����
    for (int i = 0; i < 3; i++)
    {
        pLine[i]->Release();
    }
}

//�����ɓ�������
void CharacterBase::OnCollision(GameObject* pTarget)
{
    //�G�ɓ�������
    if (pTarget->GetObjectName() == "Enemy" || pTarget->GetObjectName() == "Fire")
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
            starNum_++;
        }
    }

    XMVECTOR vCharacterBasePos = XMLoadFloat3(&transform_.position_);
    XMVECTOR Down = { 0,-1,0,0 };

    //�G�ɓ�������
    if (pTarget->GetObjectName() == "Fire")
    {
        //�G�̈ʒu
        XMFLOAT3 EnemyPos = pTarget->GetPosition();
        XMVECTOR vEnemyPos = XMLoadFloat3(&EnemyPos);

        //�v���C���[�̈ʒu
        XMVECTOR CharacterBasePos = vEnemyPos - vCharacterBasePos;
        XMVector3Normalize(CharacterBasePos);

        //Down�ƃv���C���[�̊O�ς����߂�
        XMVECTOR vDot = XMVector3Dot(Down, CharacterBasePos);
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
        }
    }
}

//���݂�����
void CharacterBase::LadderLottery()
{
    //////////////////�ǂƂ̏Փ˔���///////////////////////
    XMINT3 obj = Math::ToXMINT(transform_.position_);

    //�ǂ̔���(��)
    if (!IsRight_ && !IsLeft_)
    {
        //�i�s�����ɓ����Ȃ�������߂��Ă���
        if (pStage->IsEmpty(obj.x + 2, obj.z))
        {
            IsReturn_ = true;
        }
        if (pStage->IsEmpty(obj.x - 2, obj.z))
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
        if (pStage->IsBridge(obj.x, obj.z - 4))
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


            switch (CharacterBaseState)
            {
            case CharacterBase::State::EGG:
                speed_ = 0.2;
                break;
            case CharacterBase::State::LARVA:
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

                switch (CharacterBaseState)
                {
                case CharacterBase::State::EGG:
                    speed_ = 0.2;
                    break;
                case CharacterBase::State::LARVA:
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

//�i�ޕ���������
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