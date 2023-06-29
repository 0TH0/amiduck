#pragma once
#include "../Engine/GameObject.h"

class GameManager: public GameObject
{
	XMINT3 randPos_;
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

	void PopStar();

	void RandStar();
};