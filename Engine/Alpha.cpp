#include "Alpha.h"
#include "Model.h"

Alpha::Alpha() : time_(0),alpha_(0),frame_(0),IsFlash_(false)
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

void Alpha::SetIsFlash(bool IsFlash)
{
	IsFlash_ = IsFlash;
}