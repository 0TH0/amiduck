#pragma once
#include "../Engine/GameObject.h"

static const int MAX_STAR = 5;
static const int MAX_STAR_AFTER_TIME = 120;

//シーンを管理するクラス
class Star : public GameObject
{
	int hModel_;
	int hPict_;    //画像番号
	int MAX_TIME;
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