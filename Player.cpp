#include "Player.h"
#include "Stage.h"
#include "PlayScene.h"
#include "Block.h"
#include "StartScene.h"
#include "Coin.h"
#include "Boss.h"
#include "Pipe_base.h"

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
    SPEED(0.3f), DUSHSPEED(0.05f),
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
    hModel_ = Model::Load("duck.fbx");
    assert(hModel_ >= 0);

    //�ʒu
    transform_.position_ = XMFLOAT3(0, 0.5, 38);
    //transform_.position_ = XMFLOAT3(0, 0.5, 2);
    transform_.rotate_ = XMFLOAT3(-30, 90, 0);
    transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35); 

    //�����蔻��
    //SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
    //AddCollider(collision);

    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);

    pText->Initialize();
}

void Player::Update()
{
    if (Input::IsKeyDown(DIK_Z))
    {
        IsPress = true;
    }
    if (IsPress)
    {
        transform_.position_.x += SPEED;
    }
    else
    {
        if (Input::IsKeyDown(DIK_Z))
        {
            IsPress = false;
        }
    }

    pStage = (Stage*)FindObject("Stage");

    // 1�t���[���O�̍��W
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);

    /////////////////////////�ړ�/////////////////////////

    //���ړ�
    if (Input::IsKey(DIK_W))
    {
        transform_.position_.x += SPEED;
    }

    //���ړ�
    if (Input::IsKey(DIK_S))
    {
        transform_.position_.x -= SPEED;
    }

    if (Input::IsKey(DIK_A))
    {
        transform_.position_.z += SPEED;
    }

    if (Input::IsKey(DIK_D))
    {
        transform_.position_.z -= SPEED;
    }

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
    if (Input::IsKeyDown(DIK_SPACE)) //&& (IsJump == 0))
    {
        //�����x
        jump_v0 = 0.2f;
        //�d��
        GRAVITY = 0.008f;

        //�����x��������
        move_.y = jump_v0;

        //�d�͂�������
        move_.y += GRAVITY;

        //�W�����v�t���O
        IsJump = 1;
    }

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

    //////////////////�ǂƂ̏Փ˔���///////////////////////
    int objX = transform_.position_.x;
    int objY = transform_.position_.y;
    int objZ = transform_.position_.z;

    ////�ǂ̔���(��)
    if (pStage->IsWall( objX, objY ,objZ))
    {
        transform_.position_.y = (int)(transform_.position_.y) + 0.8;
        IsJump = 0;
    }

    if (pStage->IsWallX(objX, objY, objZ))
    {
        transform_.position_.y = (int)(transform_.position_.y) + 0.8;
        IsJump = 0;
    }

    if (pStage->IsWallM(objX, objY, objZ - 3))
    {
        a = true;
        time3++;
    }
    else
    {
        if (pStage->IsPipe(objX, objY, objZ + 2))
        {
            b = true;
        }
    }


    if (a)
    {
        time1++;
        if (time1 > 10)
        {
            trans[0].position_ = transform_.position_;
            transform_.position_.z -= 6;
            time1 = 0;
            a = false;
        }
    }
    else
    {
        if (b)
        {
            time2++;
            if (time2 > 10)
            {
                trans[1].position_ = transform_.position_;
                transform_.position_.z += 6;
                time2 = 0;
                b = false;
            }
        }
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

     //�J������]
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y -= 1.0f;
    }

    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y += 1.0f;
    }

    if (Input::IsKey(DIK_UP))
    {
        transform_.rotate_.x += 1.0f;
    }

    if (Input::IsKey(DIK_DOWN))
    {
        transform_.rotate_.x -= 1.0f;
    }

    //��]�s��
    XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    XMMATRIX mRotateY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mRotate = mRotateX * mRotateY;

    //���݈ʒu���x�N�g���ɂ��Ă���
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //�ړ��x�N�g��
    XMFLOAT3 move = { 0, 0, 0.2f };
    XMVECTOR vMove = XMLoadFloat3(&move);
    vMove = XMVector3TransformCoord(vMove, mRotate);

    XMFLOAT3 X = { 0.2f, 0, 0 };
    XMVECTOR vX = XMLoadFloat3(&X);
    vX = XMVector3TransformCoord(vX, mRotate);

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

    //�J����
    XMVECTOR vCam = XMVectorSet(0, 10, -10, 0);
    vCam = XMVector3TransformCoord(vCam, mRotate);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);
    Camera::SetPosition(camPos);
    Camera::SetTarget(transform_.position_);


    XMFLOAT3 a = Input::GetMousePosition();

    XMFLOAT3 b = Input::GetMouseMove();

    float x = b.z - a.z;

    float y =  b.z - a.z;

    transform_.rotate_.x += x * 0.025;

    if (transform_.rotate_.x > 40)  transform_.rotate_.x = 40;
    if (transform_.rotate_.x < -40) transform_.rotate_.x = -40;

    FollowGround();
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
}

void Player::Release()
{
}

////�����ɓ�������
//void Player::OnCollision(GameObject* pTarget)
//{
//    XMVECTOR vPlayerPos = XMLoadFloat3(&transform_.position_);
//    XMVECTOR Down = { 0,-1,0,0 };
//
//    float objX = transform_.position_.x;
//    float objY = transform_.position_.y;
//
//    //�u���b�N�ɓ�������
//    if (pTarget->GetObjectName() == "Block")
//    {
//        if (pStage->IsWallX((int)objX, (int)(objY + 0.2f)))
//        {
//            pTarget->KillMe();
//            IsJump = 0;
//        }
//    }
//
//    //�R�C���ɓ�������
//    if (pTarget->GetObjectName() == "Coin")
//    {
//        pTarget->KillMe();
//    }
//
//    //�G�ɓ�������
//    if (pTarget->GetObjectName() == "Enemy")
//    {
//        //�G�̈ʒu
//        XMFLOAT3 EnemyPos = pTarget->GetPosition();
//        XMVECTOR vEnemyPos = XMLoadFloat3(&EnemyPos);
//
//        //�v���C���[�̈ʒu
//        XMVECTOR PlayerPos = vEnemyPos - vPlayerPos;
//        XMVector3Normalize(PlayerPos);
//
//        //Down�ƃv���C���[�̊O�ς����߂�
//        XMVECTOR vDot = XMVector3Dot(Down, PlayerPos);
//        float Dot = XMVectorGetY(vDot);
//
//        //�p�x�����߂�
//        angle = acos(Dot) * (180.0 / 3.14f);
//
//        if (angle <= 90)
//        {
//            //�����x
//            jump_v0 = 0.15f;
//            //�d��
//            GRAVITY = 0.003f;
//
//            //�����x��������
//            move_.y = jump_v0;
//            transform_.position_.y += move_.y;
//
//            //�d�͂�������
//            move_.y += GRAVITY;
//            transform_.position_.y += move_.y;
//        }
//        else
//        {
//            SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
//            pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
//            KillMe();
//        }
//    }
//
//    //�����u���b�N�ɓ�������
//    if (pTarget->GetObjectName() == "Block_move")
//    {
//        //�ǂ̔���(��)
//        if (pStage->IsWallM((int)objX, (int)(objY + 0.2f)))
//        {
//            transform_.position_.y = (float)(int)(transform_.position_.y + 0.5f) - 0.2f;
//            IsJump = 0;
//        }
//        //�ǂ̔���i��j
//        if (pStage->IsWallM((int)objX, (int)(objY - 0.2f)))
//        {
//            transform_.position_.y = (float)(int)(transform_.position_.y) + 0.2f;
//            IsJump = 0;
//        }
//        //�ǂ̔���(�E)
//        if (pStage->IsWallM((int)(objX + 0.4f), (int)objY))
//        {
//            transform_.position_.x = (float)(int)(transform_.position_.x + 0.5f) - 0.4f;
//        }
//
//        //�ǂ̔���(��)
//        if (pStage->IsWallM((int)(objX - 0.4f), (int)objY))
//        {
//            transform_.position_.x = (float)(int)(transform_.position_.x) + 0.4f;
//        }
//    }
//
//    //�y�ǂɓ�������
//    if (pTarget->GetObjectName() == "Pipe_base")
//    {
//        //�ǂ̔���(��)
//        if (pStage->IsPipe((int)objX, (int)(objY - 0.2f)))
//        {
//            transform_.position_.y = (float)(int)(transform_.position_.y) + 0.2f;
//            IsJump = 0;
//        }
//
//        //�ǂ̔���(��)
//        if (pStage->IsPipe((int)objX, (int)(objY + 0.2f)))
//        {
//            transform_.position_.y = (float)(int)(transform_.position_.y + 0.5f) - 0.4f;
//            move_.y = -GRAVITY;
//        }
//
//        //�ǂ̔���(�E)
//        if (pStage->IsPipe((int)(objX + 0.4f), (int)objY))
//        {
//            transform_.position_.x = (float)(int)(transform_.position_.x + 0.5f) - 0.4f;
//        }
//
//        //�ǂ̔���(��)
//        if (pStage->IsPipe((int)(objX - 0.4f), (int)objY))
//        {
//            transform_.position_.x = (float)(int)(transform_.position_.x) + 0.4f;
//        }
//    }
//
//    //�{�X�ɓ�������
//    if (pTarget->GetObjectName() == "Boss")
//    {
//        //�G�̈ʒu
//        XMFLOAT3 BossPos = pTarget->GetPosition();
//        XMVECTOR vBossPos = XMLoadFloat3(&BossPos);
//
//        //�v���C���[�̈ʒu
//        XMVECTOR PlayerPos = vBossPos - vPlayerPos;
//        XMVector3Normalize(PlayerPos);
//
//        //Down�ƃv���C���[�̊O�ς����߂�
//        XMVECTOR vDot = XMVector3Dot(Down, PlayerPos);
//        float Dot = XMVectorGetY(vDot);
//
//        //�p�x�����߂�
//        angle = acos(Dot) * (180.0 / 3.14f);
//
//        if (angle <= 90)
//        {
//            //�����x
//            jump_v0 = 0.15f;
//            //�d��
//            GRAVITY = 0.003f;
//
//            //�����x��������
//            move_.y = jump_v0;
//            transform_.position_.y += move_.y;
//
//            //�d�͂�������
//            move_.y += GRAVITY;
//            transform_.position_.y += move_.y;
//
//            pTarget->KillMe();
//        }
//        else
//        {
//            //�����瓖��������v���C���[������
//            SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
//            pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
//            KillMe();
//        }
//    }
//
//    //�{�X2�ɓ�������
//    if (pTarget->GetObjectName() == "Boss2")
//    {
//        //�G�̈ʒu
//        XMFLOAT3 Boss2Pos = pTarget->GetPosition();
//        XMVECTOR vBoss2Pos = XMLoadFloat3(&Boss2Pos);
//
//        //�v���C���[�̈ʒu
//        XMVECTOR PlayerPos = vBoss2Pos - vPlayerPos;
//        XMVector3Normalize(PlayerPos);
//
//        //Down�ƃv���C���[�̊O�ς����߂�
//        XMVECTOR vDot = XMVector3Dot(Down, PlayerPos);
//        float Dot = XMVectorGetY(vDot);
//
//        if (angle <= 90)
//        {
//            //�����x
//            jump_v0 = 0.15f;
//            //�d��
//            GRAVITY = 0.003f;
//
//            //�����x��������
//            move_.y = jump_v0;
//            transform_.position_.y += move_.y;
//
//            //�d�͂�������
//            move_.y += GRAVITY;
//            transform_.position_.y += move_.y;
//
//            //HP�����炷
//            BossHp--;
//
//            //HP���O�ɂȂ��������
//            if (BossHp <= 0)
//            {
//                pTarget->KillMe();
//            }
//        }
//        else
//        {
//            //�����瓖��������v���C���[������
//            SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
//            pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
//            KillMe();
//        }
//    }
//}

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