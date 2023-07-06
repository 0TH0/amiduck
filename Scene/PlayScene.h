#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Timer.h"

//■■シーンを管理するクラス
class PlayScene : public GameObject
{
	Timer* pTimer;
	int hAudio_;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};