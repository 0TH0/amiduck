#include "Instructions.h"

#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

//コンストラクタ
Instructions::Instructions(GameObject* parent)
	: GameObject(parent, "Instructions")
{
}

//初期化
void Instructions::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("Image\\Instruction.png");
	assert(hPict_ >= 0);
	transform_.position_ = XMFLOAT3(0, -0.95f, 0);
}

//更新
void Instructions::Update()
{
}

//描画
void Instructions::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void Instructions::Release()
{
}