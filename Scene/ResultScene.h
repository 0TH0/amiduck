#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Text.h"

//テストシーンを管理するクラス
class ResultScene : public GameObject
{
public:
	enum class UIName
	{
		FINISH = 0,
		RETRY,
		BACK_TITLE,
		RESULT,
		UI_MAX
	} UIName_;

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ResultScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};