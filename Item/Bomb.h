#pragma once
#include "../Engine/GameObject.h"
#include "../Stage.h"
#include "../Engine/VFX.h"

//シーンを管理するクラス
class Bomb : public GameObject
{
public:
	int hModel_;
	Transform PlayerTrans_;
	float plus;
	EmitterData data;
	int time;
	int starDelay_;
	Stage* pStage;
	float speed_;        //移動速度
	bool IsReturn_;

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Bomb(GameObject* parent);

	~Bomb() override;

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