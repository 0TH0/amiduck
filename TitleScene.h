#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//テストシーンを管理するクラス
class TitleScene : public GameObject
{
	int hPict_;
	int hPictCh_;
	int hPictTuto_;
	int hPictStart_;
	int hPictPlay_;
	int alpha_ = 256;
	bool Is_;
	Text* pText;

	enum class BtState
	{
		NONE = 0,
		PLAY,
		Tutorial
	} btState_;

public:
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