#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine//Text.h"

class Coin : public GameObject
{
    //ïœêî
    int hModel_;
    Stage* pStage;
    Text* pText;

public:
    Coin(GameObject* parent);

    ~Coin();

    void Initialize() override;

    void Update() override;

    void Draw() override;

    void Release() override;

    void OnCollision(GameObject* pTarget) override;
};