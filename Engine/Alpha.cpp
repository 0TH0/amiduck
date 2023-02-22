#include "Alpha.h"
#include "Model.h"

Alpha::Alpha() : time_(0),alpha_(256),frame_(0),IsFlash_(false)
{
}

Alpha::~Alpha()
{
}

void Alpha::FlashModel(int frame)
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
	}
}

void Alpha::FlashImage(int frame)
{
	if (alpha_ >= 256)
	{
		IsFlash_ = true;
	}
	else if (alpha_ <= 0)
	{
		IsFlash_ = false;
	}

	if (IsFlash_)
	{
		alpha_ -= 5;
	}
	else
	{
		alpha_ += 5;
	}
}

void Alpha::FlashImage2(int frame)
{
	time_++;

	if (time_ % 10 == 0)
	{
		alpha_ = 64;
	}
	else if (time_ % 5 == 0)
	{
		alpha_ = 128;
	}
}

void Alpha::SetIsFlash(bool IsFlash)
{
	IsFlash_ = IsFlash;
}

void Alpha::FadeOutImage(int frame)
{
	if (alpha_ <= 0)
	{
		alpha_ = 0;
	}
	else
	{
		alpha_ -= frame;
	}
}