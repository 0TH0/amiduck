#pragma once
#include "GameObject.h"
#include "Fbx.h"

//-----------------------------------------------------------
//カメラ
//-----------------------------------------------------------
namespace Camera
{
	//初期化（プロジェクション行列作成）
	void Initialize();

	//更新（ビュー行列作成）
	void Update();

	//視点（カメラの位置）を設定
	void SetPosition(XMFLOAT3 position);

	//焦点（見る位置）を設定
	void SetTarget(XMFLOAT3 target);

	//位置を取得
	XMFLOAT3 GetPosition();

	//焦点を取得
	XMFLOAT3 GetTarget();

	//ビュー行列を取得
	XMMATRIX GetViewMatrix();

	//プロジェクション行列を取得
	XMMATRIX GetProjectionMatrix();

	//ビルボード用回転行列を取得
	XMMATRIX GetBillboardMatrix();

	void SetDefault();

	void SetDual();

	int GetDual();

	//ビューポート行列を取得
	XMMATRIX GetViewPortMatrix();

	//スクリーン座標からワールド座標に計算する
	void CalcScreenToWorld(RayCastData& rayData);
	
	//スタート位置のベクトル取得
	XMVECTOR GetvStart();

	//ターゲット位置のベクトル取得
	XMVECTOR GetvTarget();

	//各逆行列を求める
	XMMATRIX CalcinvTransform();

	//スタート位置のベクトル取得
	XMFLOAT3 &GetMousePosBack();

	//ターゲット位置のベクトル取得
	XMFLOAT3 &GetMousePosFront();

	float GetScrWDiv2();

	float GetScrHDiv2();
};