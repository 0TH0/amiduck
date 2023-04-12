#pragma once
#include "Engine/GameObject.h"
#include "Engine/Particle.h"

//テストシーンを管理するクラス
class Mushroom : public GameObject
{
	int hModel_;
	Particle* pParticle_;
	Transform trans;
	bool first_;
	bool right_; //右周りにするか
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Mushroom(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetRight(bool right) { right_ = right; };
};