#pragma once
#include "Engine/GameObject.h"

class Stage : public GameObject
{
    int hModel_[20];
    int map_[180][150];

public:

    Stage(GameObject* parent);

    ~Stage();

    void Initialize() override;

    void Update() override;

    void Draw() override;

    void Release() override;

    //�����͕ǂȂ̂�
    bool IsWall(int x, int y);

    bool IsWallX(int x, int y);

    bool IsWallM(int x, int y);

    bool IsPipe(int x, int y);
};