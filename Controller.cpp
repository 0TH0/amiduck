#include "Controller.h"
#include "Controller.h"
#include "Engine/Model.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Player.h"
#include "Engine/Camera.h"
#include "Enemy.h"

//コンストラクタ
Controller::Controller(GameObject* parent)
    : GameObject(parent, "Controller"), hModel_(-1)
{
}

//初期化
void Controller::Initialize()
{
    transform_.rotate_ = XMFLOAT3(-25, 90, 0);
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
    PlayerPos_ = pPlayer->GetPosition();
    transform_.position_ = PlayerPos_;

    //カメラ回転
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

    //回転行列
    XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    XMMATRIX mRotateY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mRotate = mRotateX * mRotateY;

    //現在位置をベクトルにしておく
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //移動ベクトル
    XMFLOAT3 move = { 0, 0, 0.2f };
    XMVECTOR vMove = XMLoadFloat3(&move);
    vMove = XMVector3TransformCoord(vMove, mRotate);

    XMFLOAT3 X = { 0.2f, 0, 0 };
    XMVECTOR vX = XMLoadFloat3(&X);
    vX = XMVector3TransformCoord(vX, mRotate);

    //カメラ
    XMVECTOR vCam = XMVectorSet(0, 10, -10, 0);
    vCam = XMVector3TransformCoord(vCam, mRotate);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);
    Camera::SetPosition(camPos);
    Camera::SetTarget(transform_.position_);


    XMFLOAT3 a = Input::GetMousePosition();

    XMFLOAT3 b = Input::GetMouseMove();

    float x = b.z - a.z;

    float y = b.z - a.z;

    transform_.rotate_.x += x * 0.025;

    mousePos_ = Input::GetMousePosition();

    if (transform_.rotate_.x > 40)  transform_.rotate_.x = 40;
    if (transform_.rotate_.x < -40) transform_.rotate_.x = -40;
}

void Controller::EnemyCamera()
{
    Enemy* pEnemy = (Enemy*)FindObject("Enemy");
    EnemyPos_ = pEnemy->GetPosition();
    transform_.position_ = EnemyPos_;

    //カメラ回転
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

    //回転行列
    XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    XMMATRIX mRotateY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mRotate = mRotateX * mRotateY;

    //現在位置をベクトルにしておく
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //移動ベクトル
    XMFLOAT3 move = { 0, 0, 0.2f };
    XMVECTOR vMove = XMLoadFloat3(&move);
    vMove = XMVector3TransformCoord(vMove, mRotate);

    XMFLOAT3 X = { 0.2f, 0, 0 };
    XMVECTOR vX = XMLoadFloat3(&X);
    vX = XMVector3TransformCoord(vX, mRotate);

    //カメラ
    XMVECTOR vCam = XMVectorSet(0, 10, -10, 0);
    vCam = XMVector3TransformCoord(vCam, mRotate);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);
    Camera::SetPosition(camPos);
    Camera::SetTarget(transform_.position_);

    XMFLOAT3 a = Input::GetMousePosition();

    XMFLOAT3 b = Input::GetMouseMove();

    float x = b.z - a.z;

    float y = b.z - a.z;

    transform_.rotate_.x += x * 0.025;

    mousePos_ = Input::GetMousePosition();

    if (transform_.rotate_.x > 40)  transform_.rotate_.x = 40;
    if (transform_.rotate_.x < -40) transform_.rotate_.x = -40;
}