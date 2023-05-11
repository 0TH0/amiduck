#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//テストシーンを管理するクラス
class Timer : public GameObject
{
	Text* pText_;
	int rimit_;	//残り時間
	int a_;
	std::string minutes;
	std::string seconds;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Timer(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};