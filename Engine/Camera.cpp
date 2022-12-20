#include "camera.h"
#include "Direct3D.h"
#include "Input.h"

XMFLOAT3 _position;
XMFLOAT3 _target;
XMMATRIX _view;
XMMATRIX _proj;
XMMATRIX _billBoard;
int dual_;
XMMATRIX _viewPort;
float _w; //スクリーン横
float _h; //スクリーン縦
float _wDiv2; //スクリーン横 / 2
float _hDiv2; //スクリーン縦 / 2

//初期化（プロジェクション行列作成）
void Camera::Initialize()
{
	_position = XMFLOAT3(0, 3, -10);	//カメラの位置
	_target = XMFLOAT3( 0, 0, 0);	//カメラの焦点
	dual_ = 1;

	_w = (FLOAT)Direct3D::screenWidth_;
	_h = (FLOAT)Direct3D::screenHeight_;
	_wDiv2 = _w / 2.0f;
	_hDiv2 = _h / 2.0f;

	//プロジェクション行列
	_proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, _w / _h / dual_ , 0.1f, 1000.0f);

	_viewPort = {
	_wDiv2,		 0, 0, 0,
		 0,-_hDiv2, 0, 0,
		 0,      0,	1, 0,
	_wDiv2,	_hDiv2, 0, 1
	};
}

//更新（ビュー行列作成）
void Camera::Update()
{
	//ビュー行列
	_view = XMMatrixLookAtLH(XMVectorSet(_position.x, _position.y, _position.z, 0),
		XMVectorSet(_target.x, _target.y, _target.z, 0), XMVectorSet(0, 1, 0, 0));

	//ビルボード行列
	//（常にカメラの方を向くように回転させる行列。パーティクルでしか使わない）
	//http://marupeke296.com/DXG_No11_ComeOnBillboard.html
	_billBoard = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), XMLoadFloat3(&_target) - XMLoadFloat3(&_position), XMVectorSet(0, 1, 0, 0));
	_billBoard = XMMatrixInverse(nullptr, _billBoard);
}

//焦点を設定
void Camera::SetTarget(XMFLOAT3 target) { _target = target; }

//位置を設定
void Camera::SetPosition(XMFLOAT3 position) { _position = position; }

//焦点を取得
XMFLOAT3 Camera::GetTarget() { return _target; }

//位置を取得
XMFLOAT3 Camera::GetPosition() { return _position; }

//ビュー行列を取得
XMMATRIX Camera::GetViewMatrix() { return _view; }

//プロジェクション行列を取得
XMMATRIX Camera::GetProjectionMatrix() { return _proj; }

//ビルボード用回転行列を取得
XMMATRIX Camera::GetBillboardMatrix() { return _billBoard; }

void Camera::SetDefault()
{
	dual_ = 1;
	//プロジェクション行列
	_proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_ / dual_, 0.1f, 1000.0f);
}

void Camera::SetDual()
{
	dual_ = 2;
	//プロジェクション行列
	_proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_ / dual_, 0.1f, 1000.0f);
}

int Camera::GetDual()
{
	return dual_;
}

//ビューポート行列を取得
XMMATRIX Camera::GetViewPortMatrix() { return _viewPort; }

//スクリーン座標からワールド座標にする
void Camera::CalcScreenToWorld(RayCastData& rayData)
{
	XMStoreFloat3(&rayData.start, Camera::GetvStart());
	XMStoreFloat3(&rayData.dir, Camera::GetvTarget());
}

//スタート位置のベクトル取得
XMVECTOR Camera::GetvStart()
{
	XMVECTOR vStart = XMVector3TransformCoord(XMLoadFloat3(&getMousePosFront()), CalcinvTransform());
	return vStart;
}

//ターゲット位置のベクトル取得
XMVECTOR Camera::GetvTarget()
{
	XMVECTOR vTarget = XMVector3TransformCoord(XMLoadFloat3(&getMousePosBack()), CalcinvTransform());
	return vTarget;
}

//各逆行列を求める
XMMATRIX Camera::CalcinvTransform()
{
	//各行列の逆行列
	XMMATRIX invVP = XMMatrixInverse(nullptr, Camera::GetViewPortMatrix());
	XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());
	XMMATRIX invPrj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());

	//逆行列の合成
	XMMATRIX invTransform = invVP * invPrj * invView;

	return invTransform;
}

//スタート位置のベクトル取得
XMFLOAT3& Camera::getMousePosFront()
{
	//マウス位置（手前）
	XMFLOAT3 mousePosFront = Input::GetMousePosition();
	mousePosFront.z = 0.0f;

	return mousePosFront;
}

//ターゲット位置のベクトル取得
XMFLOAT3& Camera::getMousePosBack()
{
	//マウス位置（奥）
	XMFLOAT3 mousePosBack = Input::GetMousePosition();
	mousePosBack.z = 1.0f;

	return mousePosBack;
}