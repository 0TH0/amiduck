#pragma once
#include "Engine/GameObject.h"

//シーンを管理するクラス
class Star : public GameObject
{
	int hModel_;
	int hPict_;    //画像番号
	int timeMax_;
	int rimit_;
	float rimitY;
	float scale_;
	float gravity_;
	float rotateSpeed_;
	bool IsHit_;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Star(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void OnCollision(GameObject* pTarget) override;
};