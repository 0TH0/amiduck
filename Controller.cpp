#include "Controller.h"
#include "Controller.h"
#include "Engine/Model.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Player.h"
#include "Engine/Camera.h"

namespace
{
    static const int MAX_ROTATE_CAMERA = 35;
    static const int MIN_ROTATE_CAMERA = -35;
    static const XMVECTOR VCAM = XMVectorSet(0, 17, -14, 0);
    static const float ROTATE_SPEED_X = 0.025f;
    static const float ROTATE_CAMERA1_Y = -90;
    static const float ROTATE_CAMERA2_Y = 90;
    static const XMFLOAT3 ROTATE = XMFLOAT3(-25, 90, 0);
}

//コンストラクタ
Controller::Controller(GameObject* parent)
    : GameObject(parent, "Controller"),Move_(0.01f),Rotate_(0.01f),PrevPosX_(0),PrevPosY_(0),cameraState_(cameraState::camera1),mousePos_({0,0,0})
{
}

//初期化
void Controller::Initialize()
{
    transform_.rotate_ = ROTATE;
}

//更新
void Controller::Update()
{
}

//描画
void Controller::Draw()
{
}

//開放
void Controller::Release()
{
}

void Controller::OnCollision(GameObject* pTarget)
{
}

void Controller::PlayerCamera()
{
    Player* pPlayer = (Player*)FindObject("Player");

    //プレイヤーの座標を入れておく
    transform_.position_ = pPlayer->GetPosition();
    //移動距離
    XMFLOAT3 move = { ZERO, ZERO, Move_ };
    XMVECTOR vMove = XMLoadFloat3(&move); //float->vector
    //左右移動
    XMFLOAT3 lrMove = { Move_, ZERO, ZERO };
    XMVECTOR vlrMove = XMLoadFloat3(&lrMove);
    //transform_.rotate_.yをラジアンに変換
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    //現在位置をベクトルに変換
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    XMMATRIX xRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    //回転行列作成
    xRotate *= mRotate;
    //ベクトルvMoveを行列mRotateで変形させる
    vMove = XMVector3TransformCoord(vMove, mRotate);
    vlrMove = XMVector3TransformCoord(vlrMove, mRotate);

    XMFLOAT3 cam = this->transform_.position_;
    XMVECTOR vCam = VCAM;
    vCam = XMVector3TransformCoord(vCam, xRotate);
    XMFLOAT3 camTar = transform_.position_;

    XMStoreFloat3(&cam, vPos + vCam);

    Camera::SetPosition(cam);
    Camera::SetTarget(camTar);

    if (Input::IsKeyDown(DIK_TAB))
    {
        switch (cameraState_)
        {
        case Controller::cameraState::camera1:
            transform_.rotate_.y = ROTATE_CAMERA1_Y;
            cameraState_ = cameraState::camera2;
            break;
        case Controller::cameraState::camera2:
            transform_.rotate_.y = ROTATE_CAMERA2_Y;
            cameraState_ = cameraState::camera1;
            break;
        }
    }

    if (Input::IsMouseButton(Input::CENTER))
    {
        CrickRight();
    }

    XMFLOAT3 mousePos = Input::GetMousePosition();

    XMFLOAT3 mouseMove = Input::GetMouseMove();

    float x = mouseMove.z - mousePos.z;

    transform_.rotate_.x += x * ROTATE_SPEED_X;

    mousePos_ = Input::GetMousePosition();

    //カメラ制限
    if (transform_.rotate_.x > MAX_ROTATE_CAMERA)  transform_.rotate_.x = MAX_ROTATE_CAMERA;
    if (transform_.rotate_.x < MIN_ROTATE_CAMERA) transform_.rotate_.x = MIN_ROTATE_CAMERA;
}

void Controller::CrickRight()
{
    if (Input::IsMouseButtonDown(Input::CENTER))
    {
        PrevPosX_ = Input::GetMousePosition().x;
    }

    float moveX;
    moveX = (Input::GetMousePosition().x - PrevPosX_) / 2;
    if (PrevPosY_ < Direct3D::screenHeight_ / 2)
    {
        moveX = -moveX;
    }

    transform_.rotate_.y -= moveX;

    PrevPosX_ = Input::GetMousePosition().x;
}