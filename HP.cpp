#include "HP.h"
#include "Engine/Gauge.h"
#include "Engine/Input.h"

namespace
{
	Gauge* pGauge;
}

//コンストラクタ
HP::HP(GameObject* parent)
	: GameObject(parent, "HP")
{
}

//初期化
void HP::Initialize()
{
	pGauge = Instantiate<Gauge>(this);
}

//更新
void HP::Update()
{
	pGauge->Damage(0.5f);

	if (Input::IsKey(DIK_SPACE))
	{
		Heel();
	}
}

//描画
void HP::Draw()
{
}

//開放
void HP::Release()
{
}

void HP::Heel()
{
	pGauge->Recovery(20);
}
