#include "Timer.h"

//�R���X�g���N�^
Timer::Timer(GameObject* parent)
	: GameObject(parent, "Timer"),rimit_(10800), a_(180)
{
}

//������
void Timer::Initialize()
{
	pText_ = new Text;
	pText_->Initialize();
}

//�X�V
void Timer::Update()
{
	rimit_ -= 1;

	//��b����
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

//�`��
void Timer::Draw()
{
	pText_->Draw(700, 100, minutes + " : " + seconds);
}

//�J��
void Timer::Release()
{
}
