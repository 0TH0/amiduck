#include "Controller.h"
#include "Controller.h"
#include "Engine/Model.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Player.h"
#include "Engine/Camera.h"
#include "Enemy.h"

//�R���X�g���N�^
Controller::Controller(GameObject* parent)
    : GameObject(parent, "Controller"), hModel_(-1)
{
}

//������
void Controller::Initialize()
{
    transform_.rotate_ = XMFLOAT3(-25, 90, 0);
}

//�X�V
void Controller::Update()
{
}

//�`��
void Controller::Draw()
{
}

//�J��
void Controller::Release()
{
}

void Controller::OnCollision(GameObject* pTarget)
{
}

void Controller::PlayerCamera()
{
    Player* pPlayer = (Player*)FindObject("Player");

    if (pPlayer != nullptr)
    {
        PlayerPos_ = pPlayer->GetPosition();
        transform_.position_ = PlayerPos_;

        //XMVECTOR vCam = XMVectorSet(0, 10, -10, 0);
        XMFLOAT3 move = { NULL, NULL, Move_ }; //�ړ��������(���̂�float)
        XMVECTOR vMove = XMLoadFloat3(&move); //float->vector�ϊ�(���ڃx�N�g���͍��Ȃ�)
        XMFLOAT3 lrMove = { Move_, NULL, NULL };	//���E�ړ�
        XMVECTOR vlrMove = XMLoadFloat3(&lrMove);
        XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y)); //transform_.rotate_.y�����W�A���ɕϊ����ĂԂ�����
        XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //���݈ʒu���x�N�g���ɕϊ�
        XMMATRIX xRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
        xRotate *= mRotate;							//��]�s��쐬
        vMove = XMVector3TransformCoord(vMove, mRotate); //�x�N�g��vMove���s��mRotate�ŕό`������
        vlrMove = XMVector3TransformCoord(vlrMove, mRotate);

        XMFLOAT3 cam = this->transform_.position_;
        XMVECTOR vCam = XMVectorSet(0, 10, -10, 0);
        vCam = XMVector3TransformCoord(vCam, xRotate);
        XMFLOAT3 camTar = transform_.position_;

        XMStoreFloat3(&cam, vPos + vCam);

        Camera::SetPosition(cam);
        Camera::SetTarget(camTar);

 /*       if (transform_.rotate_.x > (float)LimRot_)
        {
            transform_.rotate_.x = (float)LimRot_;
        }
        if (transform_.rotate_.x < (float)-LimRot_)
        {
            transform_.rotate_.x = (float)-LimRot_;
        }*/

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

        if (Input::IsKey(DIK_1))
        {
            transform_.rotate_.y = -90;
        }
        if (Input::IsKey(DIK_2))
        {
            transform_.rotate_.y = 90;
        }

        if (Input::IsMouseButton(1))	//�����I�ȏ�����
        {
            CrickWheel();
        }

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

        ////�J����
        //XMVECTOR vCam = XMVectorSet(0, 10, -10, 0);
        //vCam = XMVector3TransformCoord(vCam, mRotate);
        //XMFLOAT3 camPos;
        //XMStoreFloat3(&camPos, vPos + vCam);
        //Camera::SetPosition(camPos);
        //Camera::SetTarget(transform_.position_);


        XMFLOAT3 a = Input::GetMousePosition();

        XMFLOAT3 b = Input::GetMouseMove();

        float x = b.z - a.z;

        float y = b.z - a.z;

        transform_.rotate_.x += x * 0.025;

        mousePos_ = Input::GetMousePosition();

        if (transform_.rotate_.x > 40)  transform_.rotate_.x = 40;
        if (transform_.rotate_.x < -40) transform_.rotate_.x = -40;
    }
}

void Controller::CrickWheel()
{
    if (Input::IsMouseButtonDown(1))	//�����I�ȏ�����
    {
        PrevPosX_ = Input::GetMousePosition().x;
        //PrevPosY_ = Input::GetMousePosition().y;
    }

    float moveX, moveY;
    moveX = (Input::GetMousePosition().x - PrevPosX_) / 2;
    //moveY = (PrevPosY_ - Input::GetMousePosition().y) / 2;

    if (PrevPosY_ < Direct3D::screenHeight_ / 2)
    {
        moveX = -moveX;
    }

    //transform_.rotate_.x += moveY;
    transform_.rotate_.y -= moveX * 1.1f;

    PrevPosX_ = Input::GetMousePosition().x;
    //PrevPosY_ = Input::GetMousePosition().y;
}


void Controller::EnemyCamera()
{
    Enemy* pEnemy = (Enemy*)FindObject("Enemy");
    if (pEnemy != nullptr)
    {
        EnemyPos_ = pEnemy->GetPosition();
        transform_.position_ = EnemyPos_;

        //��]�s��
        XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
        XMMATRIX mRotateY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
        XMMATRIX mRotate = mRotateX * mRotateY;

        //���݈ʒu���x�N�g���ɂ��Ă���
        XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

        //�ړ��x�N�g��
        XMFLOAT3 move = { 0, 0, 0.2 };
        XMVECTOR vMove = XMLoadFloat3(&move);
        vMove = XMVector3TransformCoord(vMove, mRotate);

        XMFLOAT3 X = { 0.2, 0, 0 };
        XMVECTOR vX = XMLoadFloat3(&X);
        vX = XMVector3TransformCoord(vX, mRotate);

        //�J����
        XMVECTOR vCam = XMVectorSet(0, 10, -10, 0);
        vCam = XMVector3TransformCoord(vCam, mRotate);
        XMFLOAT3 camPos;
        XMStoreFloat3(&camPos, vPos + vCam);
        Camera::SetPosition(camPos);
        Camera::SetTarget(transform_.position_);
    }
}