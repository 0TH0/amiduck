#pragma once
#include "../Engine/GameObject.h"

class GameManager: public GameObject
{
	enum
	{
		RED,
		BLUE,
		GREEN,
		ENEMY_MAX
	};
	XMINT3 randPos_;
	int EnemyTime_[ENEMY_MAX];
	int MAX_TIME;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	GameManager(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//星を出す
	void PopStar();

	//ランダム
	void RandObject();

	//敵復活
	void EnemyReturn();
};