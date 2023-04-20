#include "Timer.h"

//コンストラクタ
Timer::Timer(GameObject* parent)
	: GameObject(parent, "Timer"),rimit_(10800)
{
}

//初期化
void Timer::Initialize()
{
	pText_ = new Text;
	pText_->Initialize();
}

//更新
void Timer::Update()
{
	rimit_ -= 1;
}

//描画
void Timer::Draw()
{
	pText_->Draw(700, 100, rimit_ % 60);
}

//開放
void Timer::Release()
{
}
