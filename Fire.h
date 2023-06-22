#pragma once
#include "Engine/GameObject.h"
#include "Engine/VFX.h"
#include "Engine/Astar.h"

//テストシーンを管理するクラス
class Fire : public GameObject
{
	int hModel_;
	Transform trans;
	bool first_;
	bool right_; //右周りにするか
	XMFLOAT3 playerPos_;
	int count_;
	Astar AI_;
	bool CanMove_;
	int totalCell;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Fire(GameObject* parent);

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