#include "Pose.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

//コンストラクタ
Pose::Pose(GameObject* parent)
	: GameObject(parent, "Pose")
{
}

//初期化
void Pose::Initialize()
{
	hPict_ = Image::Load("UI\\pose.png");
	assert(hPict_ >= 0);

	hPict2_ = Image::Load("UI\\black.png");
	assert(hPict2_ >= 0);

	transform_.position_ = XMFLOAT3(-0.8, 0.75, 0);
}

//更新
void Pose::Update()
{
	if (Image::IsHitCursor(hPict_) && (Input::IsMouseButtonDown(0)))
	{
		if (!IsPose_)
		{
			IsPose_ = true;
		}
		else
		{
			IsPose_ = false;
		}
	}
}

//描画
void Pose::Draw()
{
	//Image::SetAlpha(hPict2_, 156.f);
	//Image::SetTransform(hPict2_, transform_);
	//Image::Draw(hPict2_);
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void Pose::Release()
{
}
