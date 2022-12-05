#pragma once
#include "Engine/GameObject.h"

//シーンを管理するクラス
class Coin : public GameObject
{
	int coin_count_;

public:

	int hModel_;
	int hPict_;    //画像番号

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Coin(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void OnCollision(GameObject* pTarget) override;

	int GetCoinCount() { return coin_count_; };

	void PlusCoinCount(int count) { coin_count_ += count; };
	
	void MinCoinCount(int count) { coin_count_ -= count; };
};