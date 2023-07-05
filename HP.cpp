#include "HP.h"
#include "Engine/Gauge.h"
#include "Engine/Input.h"

namespace
{
	Gauge* pGauge;
}

//�R���X�g���N�^
HP::HP(GameObject* parent)
	: GameObject(parent, "HP")
{
}

//������
void HP::Initialize()
{
	pGauge = Instantiate<Gauge>(this);
}

//�X�V
void HP::Update()
{
	pGauge->Damage(0.5f);

	if (Input::IsKey(DIK_SPACE))
	{
		Heel();
	}
}

//�`��
void HP::Draw()
{
}

//�J��
void HP::Release()
{
}

void HP::Heel()
{
	pGauge->Recovery(20);
}
