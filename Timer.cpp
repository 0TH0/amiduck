#include "Timer.h"

//コンストラクタ
Timer::Timer(GameObject* parent)
	: GameObject(parent, "Timer"),frame_(0), rimit_(0)
{
}

//初期化
void Timer::Initialize()
{
	pText_ = new Text;
	pText_->Initialize();
	float scale = 2.5f;
	pText_->SetScale({ scale,scale,scale });
}

//更新
void Timer::Update()
{
	frame_++;

	//一秒毎に
	if (frame_ % 60 == 0 && rimit_ > 0)
	{
		rimit_--;
	}

	//分を求める
	minStr_ = std::to_string(rimit_ / 60);
	//秒を求める
	secStr_ = std::to_string(rimit_ % 60);

	//0を00にする
	if (minStr_ == "0") minStr_ = "00";
	if (secStr_ == "0") secStr_ = "00";

	//残りの時間（分）が一桁になったら
	if (minStr_.length() == 1) minStr_ = minStr_.replace(0, 2, "0" + minStr_);
	//残りの時間（秒）が一桁になったら
	if (secStr_.length() == 1) secStr_ = secStr_.replace(0 , 2, "0" + secStr_);
}

//描画
void Timer::Draw()
{
	pText_->Draw(700, 100, minStr_ + " : " + secStr_);
}

//開放
void Timer::Release()
{
	pText_->Release();
}
