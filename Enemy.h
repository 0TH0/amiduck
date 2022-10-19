#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Player.h"

class Enemy : public GameObject
{
    //ïœêî
    int hModel_;
    Stage* pStage;
    Player* pPlayer;
    XMFLOAT3 move_;
    float SPEED;
    float GRAVITY;

public:
    Enemy(GameObject* parent);

    ~Enemy();

    void Initialize() override;

    void Update() override;

    void Draw() override;

    void Release() override;

    void OnCollision(GameObject* pTarget) override;

    XMFLOAT3 GetPosition() { return transform_.position_; }
};