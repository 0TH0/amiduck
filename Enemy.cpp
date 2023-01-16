#include "Enemy.h"
#include "Stage.h"
#include "PlayScene.h"
#include "StartScene.h"

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
    jump_v0(0), gravity(0), angle(0), BossHp(3), hModelBlock_(-1),

    //�t���O
    IsJump(false), IsGround(false),

    //�萔
    SPEED(0.3f), DUSHSPEED(0.05f),
    CAMERA_POS_Y(-15.0f), CAMERA_TAR_Y(-5.0f)
{
}

//�f�X�g���N�^
Enemy::~Enemy()
{
}

void Enemy::EnemyLoad()
{
    hModel_ = Model::Load("Model\\Player\\egg.fbx");
    assert(hModel_ >= 0);
}

//������
void Enemy::Initialize()
{
    EnemyLoad();

    //�A�j���[�V�����̐ݒ�
    Model::SetAnimFrame(hModel_, 0, 300, 2.0f);

    //�ʒu
    transform_.position_ = XMFLOAT3(178, 0.5, 38);
    //transform_.position_ = XMFLOAT3(0, 0.5, 2);
    transform_.rotate_ = XMFLOAT3(0, rotate_.y, 0);
    transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35);

    //�����蔻��
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
    AddCollider(collision);

    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);

    pText->Initialize();
}

void Enemy::Update()
{
    transform_.rotate_ = XMFLOAT3(0, rotate_.y, 0);

    pStage = (Stage*)FindObject("Stage");

    // 1�t���[���O�̍��W
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);

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

    ////�W�����v���̏d��
    if (IsJump == 1)
    {
        //�d��
        move_.y -= gravity;
        transform_.position_.y += move_.y;
    }

    //�W�����v���ĂȂ����̏d��
    if (IsJump == 0)
    {
        //�d��
        gravity = 0.1f;

        //�d�͂�������
        move_.y = -gravity;
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

    ////0.1f�ȏ�̎��͎��s���Ȃ�
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
    //    transform_.rotate_.y = angle * STAGE_SIZE_X.0f / 3.1f4f;
    //}

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
    if (pStage->IsBridge(objX, objZ))
    {
        transform_.position_.y = (int)(transform_.position_.y) + 0.8;
        IsJump = 0;
    }

    if (!a && !b && pStage->IsEmpty((float)objX + 3,  objZ))
    {
        IsReturn = true;
    }
    if (!a && !b && pStage->IsEmpty((float)objX - 2.5,  objZ))
    {
        IsReturn = false;
    }

    if (IsReturn)
    {
        transform_.position_.x -= SPEED;
        rotate_.y = 0;
    }
    else
    {
        transform_.position_.x += SPEED;
        rotate_.y = Stage::GetStageSizeX();
    }


    ///////////////////////// ���݂������̏��� ///////////////////////////////////////////

    if (!b && time2 > 4)
    {
        if (pStage->IsBridge(objX,  objZ - 3))
        {
            SPEED = 0;
            a = true;
            time2 = 0;
        }
    }

    //�E�ɍs��
    if (a)
    {
        rotate_.y = -90;
        if (g <= 0)
        {
            s = 0.2;
            t += s;
            if (t >= 6)
            {
                trans[0].position_ = transform_.position_;
                time1 = 0;
                s = 0;
                t = 0;
                a = false;
                SPEED = 0.3;
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
        time2++;

        if (!b) time1++;

        if (time1 > 4)
        {
            if (pStage->IsBridge(objX,  objZ + 2))
            {
                SPEED = 0;
                b = true;
            }
        }

        if (b)
        {
            rotate_.y = 90;
            f = 0.2;
            g += f;
            if (g >= 6)
            {
                trans[1].position_ = transform_.position_;
                time2 = 0;
                g = 0;
                f = 0;
                b = false;
                SPEED = 0.3;
                time1 = 0;
            }
            else
            {
                transform_.position_.z += f;
            }
        }
    }

    //if (Input::IsKeyDown(DIK_Z))
    //{
    //    IsPress = true;
    //}
    //if (Input::IsKeyDown(DIK_X))
    //{
    //    IsPress = false;
    //}
    //if (Input::IsKeyDown(DIK_C))
    //{
    //    SPEED = -0.2;
    //}
    //if (Input::IsKeyDown(DIK_V))
    //{
    //    SPEED = 0.2;
    //}
    //if (IsPress)
    //{
    //}

    //if (pStage->IsBridge(objX, objY, objZ + 2))
    //{
    //    transform_.position_.z += 12;
    //}

    //
    ////�ǂ̔���(��)
    //if (pStage->IsWall((int)objX, (int)(objY + 0.2)))
    //{
    //    transform_.position_.y = (float)(int)(transform_.position_.y + 0.5f) - 0.4f;
    //    move_.y = -gravity;
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

    // //�J������]
    //if (Input::IsKey(DIK_LEFT))
    //{
    //    transform_.rotate_.y -= 1.0f;
    //}

    //if (Input::IsKey(DIK_RIGHT))
    //{
    //    transform_.rotate_.y += 1.0f;
    //}

    //if (Input::IsKey(DIK_UP))
    //{
    //    transform_.rotate_.x += 1.0f;
    //}

    //if (Input::IsKey(DIK_DOWN))
    //{
    //    transform_.rotate_.x -= 1.0f;
    //}

    ////��]�s��
    //XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    //XMMATRIX mRotateY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    //XMMATRIX mRotate = mRotateX * mRotateY;

    ////���݈ʒu���x�N�g���ɂ��Ă���
    //XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    ////�ړ��x�N�g��
    //XMFLOAT3 move = { 0, 0, 0.2 };
    //XMVECTOR vMove = XMLoadFloat3(&move);
    //vMove = XMVector3TransformCoord(vMove, mRotate);

    //XMFLOAT3 X = { 0.2, 0, 0 };
    //XMVECTOR vX = XMLoadFloat3(&X);
    //vX = XMVector3TransformCoord(vX, mRotate);

    //////�J�����ړ�
    //if (Input::IsKey(DIK_W))
    //{
    //    vPos += vMove;
    //    XMStoreFloat3(&transform_.position_, vPos);
    //}

    //if (Input::IsKey(DIK_S))
    //{
    //    vPos -= vMove;
    //    XMStoreFloat3(&transform_.position_, vPos);
    //}

    //if (Input::IsKey(DIK_D))
    //{
    //    vPos += vX;
    //    XMStoreFloat3(&transform_.position_, vPos);
    //}

    //if (Input::IsKey(DIK_A))
    //{
    //    vPos -= vX;
    //    XMStoreFloat3(&transform_.position_, vPos);
    //}

    ////�J����
    //XMVECTOR vCam = XMVectorSet(0, 10, -10, 0);
    //vCam = XMVector3TransformCoord(vCam, mRotate);
    //XMFLOAT3 camPos;
    //XMStoreFloat3(&camPos, vPos + vCam);
    //Camera::SetPosition(camPos);
    //Camera::SetTarget(transform_.position_);


    //XMFLOAT3 a = Input::GetMousePosition();

    //XMFLOAT3 b = Input::GetMouseMove();

    //float x = b.z - a.z;

    //float y = b.z - a.z;

    //transform_.rotate_.x += x * 0.025;

    //if (transform_.rotate_.x > 40)  transform_.rotate_.x = 40;
    //if (transform_.rotate_.x < -40) transform_.rotate_.x = -40;

    //FollowGround();

    if (!(IsVisibled()))
    {
        //�N���A�V�[���ɐ؂�ւ�
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_CLEAR);
    }
}

void Enemy::Draw()
{
    Model::SetTransform(hModel_, transform_);

    if (IsVisibled())
    {
        Model::Draw(hModel_);
    }
}

void Enemy::Release()
{
}