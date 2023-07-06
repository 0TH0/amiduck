#pragma once
#include "../Engine/GameObject.h"

//テストシーンを管理するクラス
class Line : public GameObject
{
public:
	int hPict_;    //画像番号
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Line(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};