#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
#include "Engine/Text.h"

//■■シーンを管理するクラス
class StartScene : public GameObject
{
	int hPict_[3];
	int alpha_;
	Text* pText;
	
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	StartScene(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};