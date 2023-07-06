#include "Instructions.h"
#include "../Engine/Image.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"

namespace
{
	static const XMFLOAT3 pos = { 0, -0.95f, 0 };
}

//コンストラクタ
Instructions::Instructions(GameObject* parent)
	: GameObject(parent, "Instructions"),hPict_(-1)
{
}

//初期化
void Instructions::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("Image\\Instruction.png");
	assert(hPict_ >= ZERO);
	transform_.position_ = pos;
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