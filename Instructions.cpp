#include "Instructions.h"
#include "PlayScene.h"

#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

//コンストラクタ
Instructions::Instructions(GameObject* parent)
	: GameObject(parent, "Instructions"), IsInstructions(false)
{
}

//初期化
void Instructions::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("Instructions.png");
	assert(hPict_ >= 0);
}

//更新
void Instructions::Update()
{
	if (Input::IsKey(DIK_K))
	{
		KillMe();
	}
}

//描画
void Instructions::Draw()
{
	Image::SetAlpha(hPict_, 150);
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void Instructions::Release()
{
}