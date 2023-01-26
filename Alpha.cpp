#include "Alpha.h"

int time_;	//時間
int alpha_;	//透明度
int frame_;	//何フレーム毎に点滅させるか
bool IsFlash_;	//フラッシュさせるか

void Alpha::FlashModel(int handle, int frame)
{
	if (IsFlash_)
	{
		time_++;

		if (time_ % frame == 0)
		{
			alpha_ = 1.f;
		}
		else
		{
			alpha_ = 0.5f;
		}

		if (time_ >= 60)
		{
			IsFlash_ = false;
			time_ = 0;
		}

		Model::Draw(handle, alpha_);
	}
	else
	{
		Model::Draw(handle);
	}
}

void Alpha::SetIsFlash(bool IsFlash)
{
	IsFlash_ = IsFlash;
}