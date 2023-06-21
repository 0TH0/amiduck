#pragma once
#include "Engine/GameObject.h"
#include "Engine/VFX.h"

//シーンを管理するクラス
class ItemBox : public GameObject
{
	int alpha_;
	int time_;
	bool IsHit_;
	
	EmitterData data;

public:

	int hModel_;
	int hPict_;    //画像番号

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ItemBox(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void OnCollision(GameObject* pTarget) override;

	void QuestionEffect();

	bool GetIsHit() { return IsHit_; };
};