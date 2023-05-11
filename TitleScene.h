#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//テストシーンを管理するクラス
class TitleScene : public GameObject
{
public:

	enum class UIName
	{
		PLAY = 0,
		Tutorial,
		Title,
		Char,
		UI_MAX
	} UIName_;

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};