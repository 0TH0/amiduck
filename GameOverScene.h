#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//テストシーンを管理するクラス
class GameOverScene : public GameObject
{
public:

	enum class UIName
	{
		FINISH = 0,
		RETRY,
		GAMEOVER,
		BACK_TITLE,
		UI_MAX
	} UIName_;

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	GameOverScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};