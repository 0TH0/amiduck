#include "Line.h"
#include "Engine/Image.h"

//コンストラクタ
Line::Line(GameObject* parent)
	: GameObject(parent, "Line")
{
}

//初期化
void Line::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("Image\\line_white.png");
	assert(hPict_ >= 0);

	Image::SetTransform(hPict_, transform_);
}

//更新
void Line::Update()
{
	if (Image::GetTime(hPict_) >= ONE_SECOND)
	{
		KillMe();
	}
}

//描画
void Line::Draw()
{
	Image::Draw(hPict_);
	Image::FlashImage2(hPict_);
}

//開放
void Line::Release()
{
}
