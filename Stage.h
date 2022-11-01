#pragma once
#include "Engine/GameObject.h"

class Stage : public GameObject
{
    int hModel_[20];
    int map_[180][1][39];
     
public:

    Stage(GameObject* parent);

    ~Stage();

    void Initialize() override;

    void Update() override;

    void Draw() override;

    void Release() override;

    //そこは壁なのか
    bool IsWall(int x, int y, int z);

    bool IsWallX(int x, int y, int z);

    bool IsWallM(int x, int y, int z);

    bool IsPipe(int x, int y, int z);

    int getModelHandle(int handle) { return hModel_[handle]; };

    void StageLoad();
};