#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
#include "Instructions.h"
#include "Engine/Text.h"
#include "Coin.h"

//■■シーンを管理するクラス
class PlayScene : public GameObject
{
public:
	Player* pPlayer;
	Text* pText;

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