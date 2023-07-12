#include "UI.h"
#include "Image.h"
#include "Input.h"

//コンストラクタ
UI::UI(GameObject* parent)
	: GameObject(parent, "UI"),hPict_(-1)
{
}

//初期化
void UI::Initialize()
{
	//画像をロード
	Load(fileName_);
}

//更新
void UI::Update()
{
	if (shouldUseHitCursor_)
	{
		if (Image::IsHitCursor(hPict_))
		{
			Image::SetColor(hPict_, 0.7f, 0.7f, 0.7f);
		}
		else
		{
			Image::SetColor(hPict_, 1, 1, 1);
		}
	}
}

//描画
void UI::Draw()
{
	Image::SetTransform(hPict_, transform_);
}

//開放
void UI::Release()
{
}

void UI::Load(std::string fileName)
{
	fileName_ = fileName;
	hPict_ = Image::Load(fileName_);
}