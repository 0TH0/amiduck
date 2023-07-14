#pragma once
#include "GameObject.h"
#include "Text.h"

//テストシーンを管理するクラス
class Timer : public GameObject
{
	Text* pText_;
	float scale_;
	unsigned int frameCount_;	//何フレーム経ったか
	unsigned int rimit_;	//残り時間
	std::string minStr_;	//残り分
	std::string secStr_;	//残り秒
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

	void SetRimit(int rimit) { rimit_ = rimit; };

	int GetRimit() { return rimit_; };
};