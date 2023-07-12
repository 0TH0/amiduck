#include "Transform.h"

float angle_;

Transform::Transform(): pParent_(nullptr)
{
	position_ = XMFLOAT3(0, 0, 0);
	rotate_ = XMFLOAT3(0, 0, 0);
	scale_ = XMFLOAT3(1, 1, 1);
	matTranslate_ = XMMatrixIdentity();
	matRotate_ = XMMatrixIdentity();
	matScale_ = XMMatrixIdentity();
}


Transform::~Transform()
{
}

void Transform::Calclation()
{
	//ˆÚ“®s—ñ
	matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

	//‰ñ“]s—ñ
	XMMATRIX rotateX, rotateY, rotateZ;
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
	matRotate_ = rotateZ * rotateX * rotateY;

	//Šg‘åk¬
	matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::GetWorldMatrix() 
{
	Calclation();
	if (pParent_)
	{
		return  matScale_ * matRotate_ * matTranslate_ * pParent_->GetWorldMatrix();
	}

	return  matScale_ * matRotate_ * matTranslate_;
}

void Transform::SetWorldMatrix(XMMATRIX mat)
{
	Calclation();
	if (pParent_)
	{
		mat = matScale_ * matRotate_ * matTranslate_ * pParent_->GetWorldMatrix();
	}

	mat = matScale_ * matRotate_ * matTranslate_;
}

//‰~‰ñ“]
XMFLOAT3 Transform::RotateAround(XMFLOAT3 center, float dis, float speed, bool right)
{
	angle_ += 3.14f / 180.f;
	//‰E‰ñ‚è‚¶‚á‚È‚¢‚È‚ç
	if (!right)
	{
		center.x = dis * cos(angle_ * speed) + center.x;
		center.z = dis * sin(angle_ * speed) + center.z;
	}
	else
	{
		center.z = dis * cos(angle_ * speed) + center.z;
		center.x = dis * sin(angle_ * speed) + center.x;
	}
	return center;
}