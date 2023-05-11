#include "Timer.h"

//コンストラクタ
Timer::Timer(GameObject* parent)
	: GameObject(parent, "Timer"),rimit_(10800), a_(180)
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

	//一秒毎に
	if (rimit_ % 60 == 0 && rimit_ >= 0)
	{
		a_ -= 1;
	}

	minutes = std::to_string(a_ / 60);
	seconds = std::to_string(a_ % 60);

	if (minutes == "0") minutes = "00";
	if (seconds == "0") seconds = "00";
	if (seconds.length() == 1) seconds = seconds.replace(0 , 2, "0" + seconds);
}

//描画
void Timer::Draw()
{
	pText_->Draw(700, 100, minutes + " : " + seconds);
}

//開放
void Timer::Release()
{
}
