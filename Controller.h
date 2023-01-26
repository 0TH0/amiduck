#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

//シーンを管理するクラス
class Controller : public GameObject
{
public:
	int hModel_;
	XMFLOAT3 PlayerPos_;
	Transform EnemyTrans_;
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
	XMFLOAT3 mousePos_;

	const char InitialState_ = 7;	//初期値
	const float Move_ = 0.01f;		//移動速度
	const char Rotate_ = 0.01;			//回転速度
	const char LimRot_ = 30;		//回転の限界値

	float PrevPosX_;
	float PrevPosY_;

	void CrickMouseRight();	//マウス右クリックによるカメラ操作
	void IOCamera();		//マウスホイールの回転によるカメラ操作
	void CrickWheel();		//マウスホイールを押下している時の操作

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Controller(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void OnCollision(GameObject* pTarget) override;

	void PlayerCamera();

	void EnemyCamera();
};