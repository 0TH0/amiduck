#include "PlaySceneGuide.h"
#include "../Engine/UI.h"
#include "../Engine/Image.h"

namespace
{
	UI* pUI;
}

//コンストラクタ
PlaySceneGuide::PlaySceneGuide(GameObject* parent)
	: GameObject(parent, "PlaySceneGuide")
{
}

//初期化
void PlaySceneGuide::Initialize()
{
	pUI = Instantiate<UI>(this);
	pUI->Load("Image\\start.png");
}

//更新
void PlaySceneGuide::Update()
{
}

//描画
void PlaySceneGuide::Draw()
{
	Image::Draw(pUI->GetHandle());
	Image::FadeoutImage(pUI->GetHandle());
}

//開放
void PlaySceneGuide::Release()
{
}
