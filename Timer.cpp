#include "Timer.h"

namespace
{
	static const int OFF = 0;
	static const int NX = 2;
	static const int MAX_LENGTH = 1;
}

//コンストラクタ
Timer::Timer(GameObject* parent)
	: GameObject(parent, "Timer"),frame_(0), rimit_(0),pText_(),scale_(3.f)
{
}

//初期化
void Timer::Initialize()
{
	pText_ = new Text;
	pText_->Initialize();
	pText_->SetScale({ scale_,scale_,scale_ });
}

//更新
void Timer::Update()
{
	frame_++;

	//一秒毎に
	if (frame_ % ONE_SECOND == ZERO && rimit_ > ZERO)
	{
		rimit_--;
	}

	//分を求める
	minStr_ = std::to_string(rimit_ / ONE_SECOND);
	//秒を求める
	secStr_ = std::to_string(rimit_ % ONE_SECOND);

	//0を00にする
	if (minStr_ == "0") minStr_ = "00";
	if (secStr_ == "0") secStr_ = "00";

	//残りの時間（分）が一桁になったら
	if (minStr_.length() == MAX_LENGTH) minStr_ = minStr_.replace(OFF, NX, "0" + minStr_);
	//残りの時間（秒）が一桁になったら
	if (secStr_.length() == MAX_LENGTH) secStr_ = secStr_.replace(OFF, NX, "0" + secStr_);
}

//描画
void Timer::Draw()
{
	pText_->Draw(transform_.position_.x, transform_.position_.z, minStr_ + " : " + secStr_);
}

//開放
void Timer::Release()
{
	pText_->Release();
}
