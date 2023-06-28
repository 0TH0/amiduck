#pragma once
#include "Engine/GameObject.h"

//テストシーンを管理するクラス
class RotateAroundBall : public GameObject
{
	int hModel_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	RotateAroundBall(GameObject* parent);

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