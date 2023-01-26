#include "Alpha.h"

int time_;	//����
int alpha_;	//�����x
int frame_;	//���t���[�����ɓ_�ł����邩
bool IsFlash_;	//�t���b�V�������邩

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