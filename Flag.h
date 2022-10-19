#pragma once
#include "Engine/GameObject.h"

class Flag : public GameObject
{
    //�ϐ�
    int hModel_;

public:
    Flag(GameObject* parent);

    ~Flag();

    void Initialize() override;

    void Update() override;

    void Draw() override;

    void Release() override;

    void OnCollision(GameObject* pTarget) override;
};