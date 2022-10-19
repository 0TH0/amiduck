#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Player.h"

class Boss2 : public GameObject
{
    //変数
    int hModel_;
    Stage* pStage;
    Player* pPlayer;
    XMFLOAT3 move_;
    float time;        //時間
    float RotateSpeed; //回転速度
    float SPEED;       //速さ
    float GRAVITY;     //重力
    bool IsJump;       //ジャンプフラグ
    float jump_v0;     //初速度

public:
    Boss2(GameObject* parent);

    ~Boss2();

    void Initialize() override;

    void Update() override;

    void Draw() override;

    void Release() override;

    void OnCollision(GameObject* pTarget) override;
};