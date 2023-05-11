#include "UI.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

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