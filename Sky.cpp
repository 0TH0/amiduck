#include "Sky.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

//コンストラクタ
Sky::Sky(GameObject* parent)
	: GameObject(parent, "Sky"), hPict_(-1)
{
}

//初期化
void Sky::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("Sky.png");
	assert(hPict_ >= 0);
}

//更新
void Sky::Update()
{
}

//描画
void Sky::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void Sky::Release()
{
}

