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
}

//更新
void Line::Update()
{
	if (Image::GetTime(hPict_) >= 60)
	{
		KillMe();
	}
}

//描画
void Line::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::FlashImage2(hPict_);
	Image::Draw(hPict_);
}

//開放
void Line::Release()
{
}
