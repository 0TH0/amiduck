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

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),

    //�ϐ�
    hModel_(-1),
    jump_v0(0), GRAVITY(0), angle(0), BossHp(3), hModelBlock_(-1),

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

    //data.textureFileName = "Particle\\Cloud.png";
    //data.positionErr = XMFLOAT3(0.1, 0, 0.1);
    //data.delay = 5;
    //data.number = 1;
    //data.lifeTime = 30;
    //data.dir = XMFLOAT3(0, 1, 0);
    //data.dirErr = XMFLOAT3(0, 0, 0);
    //data.speed = 0.2f;
    //data.accel = 0.98;
    //data.speedErr = 0.0;
    //data.size = XMFLOAT2(2, 2);
    //data.sizeErr = XMFLOAT2(0.4, 0.4);
    //data.scale = XMFLOAT2(1.01, 1.01);
    //data.color = XMFLOAT4(1, 1, 1, 0.2);
    //data.deltaColor = XMFLOAT4(0, 0, 0, -0.002);

    //data.delay = 0;
    //data.number = 80;
    //data.lifeTime = 100;
    //data.positionErr = XMFLOAT3(0.5, 0, 0.5);
    //data.dir = XMFLOAT3(0, 1, 0);
    //data.dirErr = XMFLOAT3(90, 90, 90);
    //data.speed = 0.25f;
    //data.speedErr = 1;
    //data.accel = 0.93;
    //data.size = XMFLOAT2(0.1, 0.1);
    //data.sizeErr = XMFLOAT2(0.4, 0.4);
    //data.scale = XMFLOAT2(0.99, 0.99);
    //data.color = XMFLOAT4(1, 0.5, 0.1, 1);
    //data.deltaColor = XMFLOAT4(0, 0, 0, 0);
    //data.gravity = 0.003f;

    //��
    {
    }
}

void Player::Update()
{
    if (Input::IsKeyDown(DIK_SPACE))
    {
        //EmitterData data;
        //data.textureFileName = "Particle\\Cloud.png";
        //data.position = transform_.position_;
        //data.positionErr = XMFLOAT3(0.1, 0, 0.1);
        //data.delay = 0;
        //data.number = 5;
        //data.lifeTime = 60;
        //data.dir = XMFLOAT3(0, 1, 0);
        //data.dirErr = XMFLOAT3(0, 0, 0);
        //data.speed = 0.01f;
        //data.speedErr = 0.0;
        //data.size = XMFLOAT2(2, 2);
        //data.sizeErr = XMFLOAT2(0.4, 0.4);
        //data.scale = XMFLOAT2(1.03, 1.02);
        //data.color = XMFLOAT4(0.7, 0.7, 0.7, 0.1);
        //pParticle_->Start(data);
        //{
        //    //�_�X�������
        //    EmitterData data;

        //    data.textureFileName = "Particle\\Cloud.png";
        //    data.position = transform_.position_;
        //    data.positionErr = XMFLOAT3(0.1, 2, 0.1);
        //    data.delay = 1;
        //    data.number = 1;
        //    data.lifeTime = 150;
        //    data.dir = XMFLOAT3(0, 1, 0);
        //    data.dirErr = XMFLOAT3(0, 0, 0);
        //    data.speed = 0.1f;
        //    data.accel = 0.98;
        //    data.speedErr = 0.5;
        //    data.size = XMFLOAT2(2, 2);
        //    data.sizeErr = XMFLOAT2(0.4, 0.4);
        //    data.scale = XMFLOAT2(1.01, 1.5);
        //    data.color = XMFLOAT4(1, 1, 1, 0.2);
        //    data.deltaColor = XMFLOAT4(0, 0, 0, -0.002);
        //    pParticle_->Start(data);
        //}
        //{
        //    EmitterData data;
        //    data.textureFileName = "Particle\\Cloud.png";
        //    data.position = transform_.position_;
        //    data.delay = 0;
        //    data.number = 80;
        //    data.lifeTime = 30;
        //    data.dir = XMFLOAT3(1, 0, 0);
        //    data.dirErr = XMFLOAT3(180, 90, 90);
        //    data.speed = 0.4f;
        //    data.speedErr = 1;
        //    data.size = XMFLOAT2(1, 0.5);
        //    data.sizeErr = XMFLOAT2(0.4, 0.4);
        //    data.scale = XMFLOAT2(1.05, 1.05);
        //    data.color = XMFLOAT4(0.2, 0.2, 1, 1);
        //    data.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);
        //    data.gravity = 0.003f;
        //    pParticle_->Start(data);

        //    data.color = XMFLOAT4(0.5, 0.5, 0, 1);
        //    pParticle_->Start(data);

        //    data.delay = 0;
        //    data.number = 80;
        //    data.lifeTime = 100;
        //    data.positionErr = XMFLOAT3(0.5, 0, 0.5);
        //    data.dir = XMFLOAT3(0, 1, 0);
        //    data.dirErr = XMFLOAT3(180, 180, 180);
        //    data.speed = 0.5f;
        //    data.speedErr = 1;
        //    data.accel = 0.93;
        //    data.size = XMFLOAT2(0.1, 0.1);
        //    data.sizeErr = XMFLOAT2(0.4, 0.4);
        //    data.scale = XMFLOAT2(0.99, 0.99);
        //    data.color = XMFLOAT4(1, 1, 0.1, 1);
        //    data.deltaColor = XMFLOAT4(0, 0, 0, 0);
        //    data.gravity = 0.003f;
        //    pParticle_->Start(data);
        //}

        //����n���Ă��Ȃ�������
        if (!is_on_bridge_)
        {
            is_Speed_up_ = true;
            Instantiate<Line>(this);
        }
    }

    if (is_Speed_up_)
    {
        speed_up_time_++;
        speed_ = 0.4;
    }
    if (speed_up_time_ > 30)
    {
        is_Speed_up_ = false;
    }


    //if (Input::IsKeyDown(DIK_SPACE))
    //{
    //    EmitterData data;
    //    data.textureFileName = "Cloud.png";
    //    data.position = XMFLOAT3(0, 0.05, 0);
    //    data.delay = 0;
    //    data.number = 80;
    //    data.lifeTime = 20;
    //    data.dir = XMFLOAT3(0, 1, 0);
    //    data.dirErr = XMFLOAT3(90, 90, 90);
    //    data.speed = 0.1f;
    //    data.speedErr = 0.8;
    //    data.size = XMFLOAT2(1, 1);
    //    data.sizeErr = XMFLOAT2(0.4, 0.4);
    //    data.scale = XMFLOAT2(1.05, 1.05);
    //    data.color = XMFLOAT4(1, 1, 0.1, 1);
    //    data.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);
    //    pParticle_->Start(data);





    //    data.delay = 0;
    //    data.number = 80;
    //    data.lifeTime = 100;
    //    data.positionErr = XMFLOAT3(0.5, 0, 0.5);
    //    data.dir = XMFLOAT3(0, 1, 0);
    //    data.dirErr = XMFLOAT3(90, 90, 90);
    //    data.speed = 0.25f;
    //    data.speedErr = 1;
    //    data.accel = 0.93;
    //    data.size = XMFLOAT2(0.1, 0.1);
    //    data.sizeErr = XMFLOAT2(0.4, 0.4);
    //    data.scale = XMFLOAT2(0.99, 0.99);
    //    data.color = XMFLOAT4(1, 1, 0.1, 1);
    //    data.deltaColor = XMFLOAT4(0, 0, 0, 0);
    //    data.gravity = 0.003f;
    //    pParticle_->Start(data);





    //}

    pStage = (Stage*)FindObject("Stage");
    Enemy* pEnemy = (Enemy*)FindObject("Enemy");


    //EnemyPos_ = pEnemy->GetPosition();
    //EnemyPos_.x = EnemyPos_.x - 5;

    //if (Input::IsKeyDown(DIK_L))
    //{
    //    transform_.position_ = EnemyPos_;
    //}

    // 1�t���[���O�̍��W
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);

    //��~����
    if (Input::IsKeyDown(DIK_F))
    {
        if (!IsStop)
        {
            speed_ = 0;
            IsStop = true;
        }
        else
        {
            speed_ = 0.3f;
            IsStop = false;
        }
    }

    /////////////////////////�ړ�/////////////////////////

    ////���ړ�
    //if (Input::IsKey(DIK_W))
    //{
    //    transform_.position_.x += SPEED;
    //}

    ////���ړ�
    //if (Input::IsKey(DIK_S))
    //{
    //    transform_.position_.x -= SPEED;
    //}

    //if (Input::IsKey(DIK_A))
    //{
    //    transform_.position_.z += SPEED;
    //}

    //if (Input::IsKey(DIK_D))
    //{
    //    transform_.position_.z -= SPEED;
    //}

    ////�E�ړ�
    //if (Input::IsKey(DIK_D))
    //{
    //    transform_.position_.x += SPEED;
    //}

    //if (Input::IsKey(DIK_W))
    //{
    //    transform_.position_.z += SPEED;
    //}

    //if (Input::IsKey(DIK_S))
    //{
    //    transform_.position_.z -= SPEED;
    //}

    ////���_�b�V��
    //if ((Input::IsKey(DIK_A)) && (Input::IsKey(DIK_B)))
    //{
    //    transform_.position_.x -= DUSHSPEED;
    //}

    ////�E�_�b�V��
    //if ((Input::IsKey(DIK_D)) && (Input::IsKey(DIK_B)))
    //{
    //    transform_.position_.x += DUSHSPEED;
    //}

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
    //    SPEED = 0;
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
        speed_ = -0.2f;
    }
    if (Input::IsKeyDown(DIK_V))
    {
        speed_ = 0.2f;
    }
    if (IsPress)
    {
    }

    //if (pStage->IsPipe(objX, objY, objZ + 2))
    //{
    //    transform_.position_.z += 12;
    //}

    //
    ////�ǂ̔���(��)
    //if (pStage->IsWall((int)objX, (int)(objY + 0.2f)))
    //{
    //    transform_.position_.y = (float)(int)(transform_.position_.y + 0.5f) - 0.4f;
    //    move_.y = -GRAVITY;
    //}

    ////�ǂ̔���(�E)
    //if (pStage->IsWall((int)(objX + 0.4f), (int)objY))
    //{
    //    transform_.position_.x = (float)(int)(transform_.position_.x + 0.5f) - 0.4f;
    //}

    ////�ǂ̔���(��)
    //if (pStage->IsWall((int)(objX - 0.4f), (int)objY))
    //{
    //    transform_.position_.x = (float)(int)(transform_.position_.x) + 0.4f;
    //}

    /////////////////////////�@�V�[���؂�ւ� ///////////////////////////

    ////��������Q�[���I�[�o�[�ɖ߂�
    //if (transform_.position_.y < 0)
    //{
    //    SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
    //    pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
    //}

    Amidakuji();

    FollowGround();

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
    if (Input::IsKeyUp(DIK_L))
    {
        Default();
    }
}

void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    pText->Draw(20, 20, "rotate.xyz");
    pText->Draw(50, 50, transform_.rotate_.x);
    pText->Draw(150, 50, transform_.rotate_.y);
    pText->Draw(250, 50, transform_.rotate_.z);

    pText->Draw(20, 100, "transform.xyz");
    pText->Draw(50, 130, transform_.position_.x);
    pText->Draw(150, 130, transform_.position_.y);
    pText->Draw(250, 130, transform_.position_.z);

    pText->Draw(100, 250, "coin");
    pText->Draw(200, 250, coin_count_);
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

    /*if (xdata.hit) a = true;
    else a = false;*/
}

void Player::Amidakuji()
{

    //////////////////�ǂƂ̏Փ˔���///////////////////////
    int objX = transform_.position_.x;
    int objY = transform_.position_.y;
    int objZ = transform_.position_.z;

    ////�ǂ̔���(��)
    if (pStage->IsWall(objX, objZ))
    {
        transform_.position_.y = (int)(transform_.position_.y) + 0.8;
        IsJump = 0;
    }
    if (pStage->IsWallX(objX, objZ))
    {
        transform_.position_.y = (int)(transform_.position_.y) + 0.8;
        IsJump = 0;
    }

    if (!IsRight_ && !IsLeft_ && pStage->IsEmpty((float)objX + 5, objZ))
    {
        IsReturn = true;
        transform_.rotate_ = XMFLOAT3(0, 0, 0);
    }
    if (!IsRight_ && !IsLeft_ && pStage->IsEmpty((float)objX - 2.5, objZ))
    {
        IsReturn = false;
        transform_.rotate_ = XMFLOAT3(0, 180, 0);
    }
    if (IsReturn)
    {
        transform_.position_.x -= speed_;
    }
    else
    {
        transform_.position_.x += speed_;
    }


    ///////////////////////// ���݂������̏��� ///////////////////////////////////////////

    if (!IsLeft_ && stopped_time_ > 4)
    {
        if (pStage->IsWallM(objX,  objZ - 3))
        {
            speed_ = 0;
            IsRight_ = true;
            stopped_time_ = 0;
            is_on_bridge_ = true;
        }
    }

    //�E�ɍs��
    if (IsRight_)
    {
        IsStop = false;

        transform_.rotate_ = XMFLOAT3(0, -90, 0);
        speed_on_wood_[right] = 0.2f;
        time_on_wood_[right] += speed_on_wood_[right];
        if (time_on_wood_[right] >= 6)
        {
            delay = 0;
            speed_on_wood_[right] = 0;
            time_on_wood_[right] = 0;
            IsRight_ = false;
            speed_ = 0.2;
            is_on_bridge_ = false;
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
            transform_.position_.z -= speed_on_wood_[right];
        }
    }

    //���ɍs��
    else
    {
        //�~�܂��Ă��Ȃ�������
        if (!IsStop)
        {
            stopped_time_++;

            if (!IsLeft_) delay++;
        }

        if (delay > 4)
        {
            if (pStage->IsPipe(objX, objZ + 2))
            {
                speed_ = 0;
                IsLeft_ = true;
                is_on_bridge_ = true;
            }
        }

        if (IsLeft_)
        {
            IsStop = false;

            speed_on_wood_[left] = 0.2f;
            time_on_wood_[left] += speed_on_wood_[left];
            transform_.rotate_ = XMFLOAT3(0, 90, 0);
            if (time_on_wood_[left] >= 6)
            {
                stopped_time_ = 0;
                time_on_wood_[left] = 0;
                speed_on_wood_[left] = 0;
                IsLeft_ = false;
                speed_ = 0.2;
                delay = 0;
                is_on_bridge_ = false;
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
                transform_.position_.z += speed_on_wood_[left];
            }
        }
    }
}

