#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/PoryLine.h"


//シーンを管理するクラス
class Fire : public GameObject
{
public:
	int hModel_; 
	Transform PlayerTrans_;
	float plus;
	bool Is;


	float a = false;
	bool c = false;
	bool b = false;
	int time1 = 0;
	int time2;
	int time3;
	Transform trans[2];
	bool IsPress;
	bool IsReturn;
	bool IsStop;
	float s;
	float t;
	float f;
	float g;

	int time;

	Stage* pStage;
	float speed_;        //移動速度
	PoryLine* pLine;
	PoryLine* pLine2;

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Fire(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void OnCollision(GameObject* pTarget) override;

};