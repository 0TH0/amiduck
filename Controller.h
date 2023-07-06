#pragma once
#include "Engine/GameObject.h"
#include "Stage/Stage.h"

//シーンを管理するクラス
class Controller : public GameObject
{
	XMFLOAT3 mousePos_;
	const float Move_;		//移動速度
	const char Rotate_;		//回転速度
	float PrevPosX_;
	float PrevPosY_;
public:

	void CrickRight();

	enum class cameraState
	{
		camera1 = 0,
		camera2
	}cameraState_;

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