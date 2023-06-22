#include "Controller.h"
#include "Controller.h"
#include "Engine/Model.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Player.h"
#include "Engine/Camera.h"


//�R���X�g���N�^
Controller::Controller(GameObject* parent)
    : GameObject(parent, "Controller"),Move_(0.01f),Rotate_(0.01f),LimRot_(30)
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

    transform_.position_ = pPlayer->GetPosition();

    XMFLOAT3 move = { 0, 0, Move_ }; //�ړ�����
    XMVECTOR vMove = XMLoadFloat3(&move); //float->vector
    XMFLOAT3 lrMove = { Move_, 0, 0 };	//���E�ړ�
    XMVECTOR vlrMove = XMLoadFloat3(&lrMove);
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y)); //transform_.rotate_.y�����W�A���ɕϊ����ĂԂ�����
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_); //���݈ʒu���x�N�g���ɕϊ�
    XMMATRIX xRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    xRotate *= mRotate;							//��]�s��쐬
    vMove = XMVector3TransformCoord(vMove, mRotate); //�x�N�g��vMove���s��mRotate�ŕό`������
    vlrMove = XMVector3TransformCoord(vlrMove, mRotate);

    XMFLOAT3 cam = this->transform_.position_;
    XMVECTOR vCam = XMVectorSet(0, 17, -14, 0);
    vCam = XMVector3TransformCoord(vCam, xRotate);
    XMFLOAT3 camTar = transform_.position_;

    XMStoreFloat3(&cam, vPos + vCam);

    Camera::SetPosition(cam);
    Camera::SetTarget(camTar);

    //�J������]
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y -= 2.0f;
    }

    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y += 2.0f;
    }

    if (Input::IsKey(DIK_UP))
    {
        transform_.rotate_.x += 2.0f;
    }

    if (Input::IsKey(DIK_DOWN))
    {
        transform_.rotate_.x -= 2.0f;
    }

    if (Input::IsKeyDown(DIK_TAB))
    {
        switch (cameraState_)
        {
        case Controller::cameraState::camera1:
            transform_.rotate_.y = -90;
            cameraState_ = cameraState::camera2;
            break;
        case Controller::cameraState::camera2:
            transform_.rotate_.y = 90;
            cameraState_ = cameraState::camera1;
            break;
        }
    }

    if (Input::IsMouseButton(1))
    {
        CrickRight();
    }

    XMFLOAT3 mousePos = Input::GetMousePosition();

    XMFLOAT3 mouseMove = Input::GetMouseMove();

    float x = mouseMove.z - mousePos.z;

    transform_.rotate_.x += x * 0.025f;

    mousePos_ = Input::GetMousePosition();

    if (transform_.rotate_.x > 35)  transform_.rotate_.x = 35;
    if (transform_.rotate_.x < -35) transform_.rotate_.x = -35;
}

void Controller::CrickRight()
{
    if (Input::IsMouseButtonDown(1))
    {
        PrevPosX_ = Input::GetMousePosition().x;
    }

    float moveX;
    moveX = (Input::GetMousePosition().x - PrevPosX_) / 2;
    if (PrevPosY_ < Direct3D::screenHeight_ / 2)
    {
        moveX = -moveX;
    }

    transform_.rotate_.y -= moveX * 1.1f;

    PrevPosX_ = Input::GetMousePosition().x;
}