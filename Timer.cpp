#include "Timer.h"

//�R���X�g���N�^
Timer::Timer(GameObject* parent)
	: GameObject(parent, "Timer"),frame_(0), rimit_(0)
{
}

//������
void Timer::Initialize()
{
	pText_ = new Text;
	pText_->Initialize();
	float scale = 2.5f;
	pText_->SetScale({ scale,scale,scale });
}

//�X�V
void Timer::Update()
{
	frame_++;

	//��b����
	if (frame_ % 60 == 0 && rimit_ > 0)
	{
		rimit_--;
	}

	//�������߂�
	minStr_ = std::to_string(rimit_ / 60);
	//�b�����߂�
	secStr_ = std::to_string(rimit_ % 60);

	//0��00�ɂ���
	if (minStr_ == "0") minStr_ = "00";
	if (secStr_ == "0") secStr_ = "00";

	//�c��̎��ԁi���j���ꌅ�ɂȂ�����
	if (minStr_.length() == 1) minStr_ = minStr_.replace(0, 2, "0" + minStr_);
	//�c��̎��ԁi�b�j���ꌅ�ɂȂ�����
	if (secStr_.length() == 1) secStr_ = secStr_.replace(0 , 2, "0" + secStr_);
}

//�`��
void Timer::Draw()
{
	pText_->Draw(700, 100, minStr_ + " : " + secStr_);
}

//�J��
void Timer::Release()
{
	pText_->Release();
}
