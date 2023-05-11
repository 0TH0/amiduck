#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//テストシーンを管理するクラス
class ClearScene : public GameObject
{
public:

	enum class UIName
	{
		FINISH = 0,
		RETRY,
		CLEAR,
		BACK_TITLE,
		UI_MAX
	} UIName_;

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ClearScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};