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

	if (rimit_ % 60 == 0)
	{
		a_ -= 1;
	}
}

//�`��
void Timer::Draw()
{
	//pText_->Draw(700, 100, a_ % 60);
}

//�J��
void Timer::Release()
{
}
