#pragma once
#include "Engine/GameObject.h"
#include "Engine/Particle.h"

//シーンを管理するクラス
class Star : public GameObject
{
	int coin_count_;
	int time_;
	bool IsHit_;
	Particle* pParticle_;
public:

	int hModel_;
	int hPict_;    //画像番号

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

	void StarEffect();
};