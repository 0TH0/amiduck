#include "Player.h"
#include "Stage.h"
#include "PlayScene.h"
#include "StartScene.h"
#include "Fire.h"
#include "Controller.h"
#include "Enemy.h"

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
    jump_v0(0), GRAVITY(0), angle(0),BossHp(3), hModelBlock_(-1),
    
    //�t���O
    IsJump(false), IsGround(false),

    //�萔
    speed(0.3f), DUSHSPEED(0.05f),
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
    hModel_ = Model::Load("Enemy\\raccoon10.fbx");
    assert(hModel_ >= 0);

    //�A�j���[�V�����̐ݒ�
    Model::SetAnimFrame(hModel_, 0, 200, 1.0f);

    //�ʒu
    transform_.position_ = XMFLOAT3(0, 0.5, 38);
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
}

void Player::Update()
{
    pStage = (Stage*)FindObject("Stage");
    Enemy* pEnemy = (Enemy*)FindObject("Enemy");

    // 1�t���[���O�̍��W
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);

    FollowGround();

    Amidakuji();

    //��~����
    if(Input::IsKeyDown(DIK_F))
    {
        if (!IsStop)
        {
            speed = 0;
            IsStop = true;
        }
        else
        {
            speed = 0.3f;
            IsStop = false;
        }
    }

    ////�J����
    //Camera::SetPosition(XMFLOAT3(transform_.position_.x, 7, CAMERA_POS_Y));
    //Camera::SetTarget(XMFLOAT3(transform_.position_.x, 7, CAMERA_TAR_Y));

    ////�J�����ړ�����
    //if (transform_.position_.x < 8.0f)
    //{
    //    Camera::SetTarget(XMFLOAT3(8, 7, -5));
    //    Camera::SetPosition(XMFLOAT3(8, 7, -15));
    //}

    //////////�W�����v///////
    //if (Input::IsKeyDown(DIK_SPACE)) //&& (IsJump == 0))
    //{
    //    ////�����x
    //    //jump_v0 = 0.2f;
    //    ////�d��
    //    //GRAVITY = 0.008f;

    //    ////�����x��������
    //    //move_.y = jump_v0;

    //    ////�d�͂�������
    //    //move_.y += GRAVITY;

    //    ////�W�����v�t���O
    //    //IsJump = 1;
    //    speed = 0;
    //}

    ////�W�����v���̏d��
    if (IsJump == 1)
    {
        //�d��
        move_.y -= GRAVITY;
        transform_.position_.y += move_.y;
    }

    //�W�����v���ĂȂ����̏d��
    if (IsJump == 0)
    {
        //�d��
        GRAVITY = 0.1f;

        //�d�͂�������
        move_.y = -GRAVITY;
        transform_.position_.y += move_.y;
    }

    //if (a)
    //{
        //if (transform_.position_.y < 1.0)
        //{
        //    transform_.position_.y = 1.0;
        //    IsJump = false;
        //}
    //}
    
    ///////////// �v���C���[�̌��� /////////////

    ////���݂̈ʒu�̃x�N�g��
    //XMVECTOR nowPosition = XMLoadFloat3(&transform_.position_);

    ////����ʒu�̃x�N�g��
    //XMVECTOR nowMove = nowPosition - prevPosition;

    ////�ړ��׃N�g��
    //XMVECTOR Length = XMVector3Length(nowMove);

    ////0.1�ȏ�̎��͎��s���Ȃ�
    //if (XMVectorGetX(Length) > 0.01)
    //{
    //    //�p�x�����߂�̂ɒ�����1�ɂ���i���K���j
    //    nowMove = XMVector3Normalize(nowMove);

    //    //��ƂȂ�����̃x�N�g��
    //    XMVECTOR front = { 0, 0, 1, 0 };

    //    //front��move�̊O�ς����߂�
    //    XMVECTOR vecDot = XMVector3Dot(front, nowMove);
    //    float dot = XMVectorGetX(vecDot);

    //    //�����Ă�p�x�����߂�(���W�A��)
    //    angle = acos(dot);

    //    //front��move�̊O�ς����߂�
    //    XMVECTOR cross = XMVector3Cross(front, nowMove);

    //    //�O�ς��}�C�i�X���Ɖ�����
    //    if (XMVectorGetY(cross) < 0)
    //    {
    //        angle *= -1;
    //    }

    //    //���̊p�x��]������
    //    transform_.rotate_.y = angle * 180.0f / 3.14f;
    //}

    //��ʐ؂�ւ�
    if (Input::IsKeyDown(DIK_Z))
    {
        Camera::SetDual();
    }
    if (Input::IsKeyDown(DIK_X))
    {
        Camera::SetDefault();
    }

    if (!IsBlend())
    {
        if (Input::IsKeyDown(DIK_L))
        {
            Blend();
            EmitterData data;
            data.textureFileName = "Particle\\Cloud.png";
            data.position = transform_.position_;
            data.positionErr = XMFLOAT3(0.1, 0, 0.1);
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
            data.color = XMFLOAT4(0.7, 0.7, 0.7, 0.1);
            pParticle_->Start(data);
        }
    }
    if (Input::IsKeyDown(DIK_K))
    {
        Default();
    }
}

void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    //pText->Draw(20, 20, "rotate.xyz");
    //pText->Draw(50, 50, transform_.rotate_.x);
    //pText->Draw(150, 50, transform_.rotate_.y);
    //pText->Draw(250, 50, transform_.rotate_.z);

    //pText->Draw(20, 100, "transform.xyz");
    //pText->Draw(50, 130, transform_.position_.x);
    //pText->Draw(150, 130, transform_.position_.y);
    //pText->Draw(250, 130, transform_.position_.z);

    //pText->Draw(100, 250, "coin");
    //pText->Draw(200, 250, coin_count_);
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
}

void Player::Amidakuji()
{
    ///////////////////////// ���݂������̏��� ///////////////////////////////////////////
    
    int objX = transform_.position_.x;
    int objY = transform_.position_.y;
    int objZ = transform_.position_.z;

    ////�ǂ̔���(��)
    if (pStage->IsWall(objX, objY, objZ))
    {
        transform_.position_.y = (int)(transform_.position_.y) + 0.8;
        IsJump = 0;
    }
    if (pStage->IsWallX(objX, objY, objZ))
    {
        transform_.position_.y = (int)(transform_.position_.y) + 0.8;
        IsJump = 0;
    }

    if (!a && !b && pStage->IsEmpty((float)objX + 5, objY, objZ))
    {
        IsReturn = true;
    }
    if (!a && !b && pStage->IsEmpty((float)objX - 2.5, objY, objZ))
    {
        IsReturn = false;
    }
    if (IsReturn)
    {
        transform_.position_.x -= speed;
    }
    else
    {
        transform_.position_.x += speed;
    }

    if (!b && time2 > 4)
    {
        if (pStage->IsWallM(objX, objY, objZ - 3))
        {
            speed = 0;
            a = true;
            time2 = 0;
        }
    }

    //�E�ɍs��
    if (a)
    {
        IsStop = false;

        transform_.rotate_ = XMFLOAT3(0, -90, 0);
        if (g <= 0)
        {
            s = 0.2f;
            t += s;
            if (t >= 6)
            {
                trans[0].position_ = transform_.position_;
                time1 = 0;
                s = 0;
                t = 0;
                a = false;
                speed = 0.2;
                if (IsReturn)
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
                transform_.position_.z -= s;
            }
        }
    }
    //���ɍs��
    else
    {
        //�~�܂��Ă��Ȃ�������
        if (!IsStop)
        {
            time2++;

            if (!b) time1++;
        }

        if (time1 > 4)
        {
            if (pStage->IsPipe(objX, objY, objZ + 2))
            {
                speed = 0;
                b = true;
            }
        }

        if (b)
        {
            IsStop = false;
            f = 0.2f;
            g += f;
            transform_.rotate_ = XMFLOAT3(0, 90, 0);
            if (g >= 6)
            {
                trans[1].position_ = transform_.position_;
                time2 = 0;
                g = 0;
                f = 0;
                b = false;
                speed = 0.2;
                time1 = 0;
                if (IsReturn)
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
                transform_.position_.z += f;
            }
        }
    }
}

//�n�ʂɉ��킹��
void Player::FollowGround()
{
    //�܂��n�ʂ̃��f���ԍ���m��Ȃ�

    //���f���ԍ��𒲂ׂ�
    hModelBlock_ = ((Stage*)FindObject("Stage"))->getModelHandle(1);
    hModelWood_ = ((Stage*)FindObject("Stage"))->getModelHandle(2);

    //���C��������
    RayCastData data;
    data.start = transform_.position_;
    data.start.y = transform_.position_.y + 1;
    data.dir = XMFLOAT3(0, -1, 0);

    RayCastData xdata;
    xdata.start = transform_.position_;
    xdata.start.y = transform_.position_.y + 1;
    xdata.dir = XMFLOAT3(0, -1, 0);
    xdata.normal;

    //�n�ʂɑ΂��ă��C������
    Model::RayCast(hModelBlock_, &data);
    Model::RayCast(hModelWood_, &xdata);

    //���C���n�ʂɓ���������
    if (data.hit)
    {
        if (transform_.position_.y - data.dist > 1)
        {
            transform_.position_.y = -data.dist;
        }
    }
    if (xdata.hit)
    {
        if (transform_.position_.y - xdata.dist > 1)
        {
            transform_.position_.y = -xdata.dist;
        }
    }
}