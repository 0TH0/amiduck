#pragma once
#include "GameObject.h"

class UI : public GameObject
{
	int hPict_;
	std::string fileName_;
	bool shouldUseHitCursor_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	UI(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	virtual void Load(std::string fileName);

	int GetHandle() { return hPict_; };

	void SetShouldUseHitCursor(bool flag) { shouldUseHitCursor_ = flag; };
	bool GetShouldUseHitCursor() {return shouldUseHitCursor_;};
};