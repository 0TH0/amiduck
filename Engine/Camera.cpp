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
float _w; //�X�N���[����
float _h; //�X�N���[���c
float _wDiv2; //�X�N���[���� / 2
float _hDiv2; //�X�N���[���c / 2

//�������i�v���W�F�N�V�����s��쐬�j
void Camera::Initialize()
{
	_position = XMFLOAT3(0, 3, -10);	//�J�����̈ʒu
	_target = XMFLOAT3( 0, 0, 0);	//�J�����̏œ_
	dual_ = 1;

	_w = (FLOAT)Direct3D::screenWidth_;
	_h = (FLOAT)Direct3D::screenHeight_;
	_wDiv2 = _w / 2.0f;
	_hDiv2 = _h / 2.0f;

	//�v���W�F�N�V�����s��
	_proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, _w / _h / dual_ , 0.1f, 1000.0f);
}

//�X�V�i�r���[�s��쐬�j
void Camera::Update()
{
	//�r���[�s��
	_view = XMMatrixLookAtLH(XMVectorSet(_position.x, _position.y, _position.z, 0),
		XMVectorSet(_target.x, _target.y, _target.z, 0), XMVectorSet(0, 1, 0, 0));

	//�r���{�[�h�s��
	//�i��ɃJ�����̕��������悤�ɉ�]������s��B�p�[�e�B�N���ł����g��Ȃ��j
	//http://marupeke296.com/DXG_No11_ComeOnBillboard.html
	_billBoard = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), XMLoadFloat3(&_target) - XMLoadFloat3(&_position), XMVectorSet(0, 1, 0, 0));
	_billBoard = XMMatrixInverse(nullptr, _billBoard);

	_w = (FLOAT)Direct3D::screenWidth_;
	_h = (FLOAT)Direct3D::screenHeight_;
	_wDiv2 = _w / 2.0f;
	_hDiv2 = _h / 2.0f;
	_viewPort = {
	_wDiv2,		 0, 0, 0,
	 0,-_hDiv2, 0, 0,
	 0,      0,	1, 0,
	_wDiv2,	_hDiv2, 0, 1
	};
}

//�œ_��ݒ�
void Camera::SetTarget(XMFLOAT3 target) { _target = target; }

//�ʒu��ݒ�
void Camera::SetPosition(XMFLOAT3 position) { _position = position; }

//�œ_���擾
XMFLOAT3 Camera::GetTarget() { return _target; }

//�ʒu���擾
XMFLOAT3 Camera::GetPosition() { return _position; }

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix() { return _view; }

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix() { return _proj; }

//�r���{�[�h�p��]�s����擾
XMMATRIX Camera::GetBillboardMatrix() { return _billBoard; }

void Camera::SetDefault()
{
	dual_ = 1;
	//�v���W�F�N�V�����s��
	_proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_ / dual_, 0.1f, 1000.0f);
}

void Camera::SetDual()
{
	dual_ = 2;
	//�v���W�F�N�V�����s��
	_proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_ / dual_, 0.1f, 1000.0f);
}

int Camera::GetDual()
{
	return dual_;
}

//�r���[�|�[�g�s����擾
XMMATRIX Camera::GetViewPortMatrix() { return _viewPort; }

//�X�N���[�����W���烏�[���h���W�ɂ���
void Camera::CalcScreenToWorld(RayCastData& rayData)
{
	XMStoreFloat3(&rayData.start, Camera::GetvStart());
	XMStoreFloat3(&rayData.dir, Camera::GetvTarget());
}

//�X�^�[�g�ʒu�̃x�N�g���擾
XMVECTOR Camera::GetvStart()
{
	XMVECTOR vStart = XMVector3TransformCoord(XMLoadFloat3(&GetMousePosFront()), CalcinvTransform());
	return vStart;
}

//�^�[�Q�b�g�ʒu�̃x�N�g���擾
XMVECTOR Camera::GetvTarget()
{
	XMVECTOR vTarget = XMVector3TransformCoord(XMLoadFloat3(&GetMousePosBack()), CalcinvTransform());
	return vTarget;
}

//�e�t�s������߂�
XMMATRIX Camera::CalcinvTransform()
{
	//�e�s��̋t�s��
	XMMATRIX invVP = XMMatrixInverse(nullptr, Camera::GetViewPortMatrix());
	XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());
	XMMATRIX invPrj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());

	//�t�s��̍���
	XMMATRIX invTransform = invVP * invPrj * invView;

	return invTransform;
}

//�X�^�[�g�ʒu�̃x�N�g���擾
XMFLOAT3& Camera::GetMousePosFront()
{
	//�}�E�X�ʒu�i��O�j
	XMFLOAT3 mousePosFront = Input::GetMousePosition();
	mousePosFront.z = 0.0f;

	return mousePosFront;
}

float Camera::GetScrWDiv2()
{
	return _wDiv2;
}

float Camera::GetScrHDiv2()
{
	return _hDiv2;
}

//�^�[�Q�b�g�ʒu�̃x�N�g���擾
XMFLOAT3& Camera::GetMousePosBack()
{
	//�}�E�X�ʒu�i���j
	XMFLOAT3 mousePosBack = Input::GetMousePosition();
	mousePosBack.z = 1.0f;

	return mousePosBack;
}