#pragma once
#include "Engine/GameObject.h"
#include "Scene/PlayScene.h"

//シーンを管理するクラス
class Instructions : public GameObject
{
public:
	int hPict_;    //画像番号
	bool IsInstructions;

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Instructions(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};