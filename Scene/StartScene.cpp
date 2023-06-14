#include "StartScene.h"
#include "../Engine/Image.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"

//コンストラクタ
StartScene::StartScene(GameObject* parent)
	: GameObject(parent, "StartScene")
{
}

//初期化
void StartScene::Initialize()
{
	Camera::SetDefault();

	hPict_[0] = Image::Load("Image\\start.png");
	assert(hPict_[0] >= 0);
}

//更新
void StartScene::Update()
{
}

//描画
void StartScene::Draw()
{
	Image::SetTransform(hPict_[0], transform_);
	Image::Draw(hPict_[0]);
	Image::FadeoutImage(hPict_[0]);
}

//開放
void StartScene::Release()
{
}